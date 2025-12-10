package com.parkinglot.service;

import java.time.LocalDateTime;
import java.util.*;
import java.util.concurrent.atomic.AtomicLong;
import java.util.stream.Collectors;

import com.parkinglot.enums.SpotStatus;
import com.parkinglot.enums.SpotType;
import com.parkinglot.enums.VehicleType;
import com.parkinglot.models.ParkingSpot;
import com.parkinglot.models.ParkingTicket;
import com.parkinglot.models.Vehicle;

public class ParkingLotManagerInMemImpl implements ParkingLotManager {

    private final ParkingSpotRepository spotRepo;
    private final TicketRepository ticketRepo;
    private final SpotAssignmentStrategy strategy;
    private final AtomicLong ticketCounter = new AtomicLong(1);

    public ParkingLotManagerInMemImpl() {
        this.spotRepo = new InMemoryParkingSpotRepository();
        this.ticketRepo = new InMemoryTicketRepository();
        this.strategy = new DefaultSpotAssignmentStrategy();
    }

    // -----------------------------------------------------------------------
    // PUBLIC API
    // -----------------------------------------------------------------------

    @Override
    public Boolean addParkingSpot(ParkingSpot spot) {
        if (spot == null || spot.getSpotId() == null) return false;
        return spotRepo.save(spot);
    }

    @Override
    public Boolean removeParkingSpot(String spotId) {
        ParkingSpot s = spotRepo.findById(spotId);
        if (s == null) return false;
        if (s.getStatus() == SpotStatus.OCCUPIED) return false;
        return spotRepo.delete(spotId);
    }

    @Override
    public ParkingTicket parkVehicle(Vehicle vehicle, LocalDateTime entryTime) {
        if (vehicle == null || entryTime == null) return null;

        // Already parked?
        if (ticketRepo.findActiveByLicense(vehicle.getLicensePlate()) != null)
            return null;

        List<ParkingSpot> available = spotRepo.findAllAvailable();
        Optional<ParkingSpot> chosen = strategy.assignSpot(vehicle, available);

        if (!chosen.isPresent()) return null;

        ParkingSpot spot = chosen.get();
        spot.setStatus(SpotStatus.OCCUPIED);
        spot.setParkedVehicleLicense(vehicle.getLicensePlate());
        spotRepo.save(spot);

        String ticketId = "T-" + ticketCounter.getAndIncrement();
        ParkingTicket ticket = new ParkingTicket(ticketId, vehicle.getLicensePlate(), spot.getSpotId(), entryTime);
        ticketRepo.save(ticket);

        return ticket;
    }

    @Override
    public Boolean exitVehicle(String licensePlate, LocalDateTime exitTime) {
        ParkingTicket ticket = ticketRepo.findActiveByLicense(licensePlate);
        if (ticket == null) return false;

        // Set exit time
        ticket.setExitTime(exitTime);
        ticketRepo.save(ticket);

        // Free spot
        ParkingSpot spot = spotRepo.findById(ticket.getSpotId());
        if (spot != null) {
            spot.setStatus(SpotStatus.AVAILABLE);
            spot.setParkedVehicleLicense(null);
            spotRepo.save(spot);
        }

        ticketRepo.deactivate(ticket.getTicketId());
        return true;
    }

    @Override
    public ParkingSpot findVehicleByLicense(String licensePlate) {
        ParkingTicket ticket = ticketRepo.findActiveByLicense(licensePlate);
        if (ticket == null) return null;
        return spotRepo.findById(ticket.getSpotId());
    }

    @Override
    public List<ParkingSpot> getAvailableSpotsByType(SpotType spotType) {
        return spotRepo.findAllAvailable().stream()
                .filter(s -> s.getSpotType() == spotType)
                .sorted(Comparator.comparingInt(ParkingSpot::getFloor)
                        .thenComparing(ParkingSpot::getSpotId))
                .collect(Collectors.toList());
    }

    @Override
    public ParkingSpot getParkingSpot(String spotId) {
        return spotRepo.findById(spotId);
    }

    // -----------------------------------------------------------------------
    // REPOSITORIES
    // -----------------------------------------------------------------------

    private interface ParkingSpotRepository {
        boolean save(ParkingSpot spot);
        ParkingSpot findById(String spotId);
        boolean delete(String spotId);
        List<ParkingSpot> findAllAvailable();
    }

    private static class InMemoryParkingSpotRepository implements ParkingSpotRepository {
        private final Map<String, ParkingSpot> spots = new HashMap<>();

        @Override
        public boolean save(ParkingSpot spot) {
            spots.put(spot.getSpotId(), cloneSpot(spot));
            return true;
        }

        @Override
        public ParkingSpot findById(String spotId) {
            ParkingSpot s = spots.get(spotId);
            return s == null ? null : cloneSpot(s);
        }

        @Override
        public boolean delete(String spotId) {
            return spots.remove(spotId) != null;
        }

        @Override
        public List<ParkingSpot> findAllAvailable() {
            return spots.values().stream()
                    .filter(s -> s.getStatus() == SpotStatus.AVAILABLE)
                    .map(InMemoryParkingSpotRepository::cloneSpot)
                    .collect(Collectors.toList());
        }

        private static ParkingSpot cloneSpot(ParkingSpot s) {
            ParkingSpot p = new ParkingSpot();
            p.setSpotId(s.getSpotId());
            p.setSpotType(s.getSpotType());
            p.setFloor(s.getFloor());
            p.setStatus(s.getStatus());
            p.setParkedVehicleLicense(s.getParkedVehicleLicense());
            return p;
        }
    }

    private interface TicketRepository {
        boolean save(ParkingTicket ticket);
        ParkingTicket findActiveByLicense(String license);
        void deactivate(String ticketId);
    }

    private static class InMemoryTicketRepository implements TicketRepository {
        private final Map<String, ParkingTicket> tickets = new HashMap<>();
        private final Map<String, String> activeTicketsByLicense = new HashMap<>();

        @Override
        public boolean save(ParkingTicket ticket) {
            tickets.put(ticket.getTicketId(), cloneTicket(ticket));
            if (ticket.getExitTime() == null)
                activeTicketsByLicense.put(ticket.getLicensePlate(), ticket.getTicketId());
            else
                activeTicketsByLicense.remove(ticket.getLicensePlate());
            return true;
        }

        @Override
        public ParkingTicket findActiveByLicense(String license) {
            String ticketId = activeTicketsByLicense.get(license);
            if (ticketId == null) return null;
            return cloneTicket(tickets.get(ticketId));
        }

        @Override
        public void deactivate(String ticketId) {
            ParkingTicket t = tickets.get(ticketId);
            if (t != null) {
                activeTicketsByLicense.remove(t.getLicensePlate());
            }
        }

        private static ParkingTicket cloneTicket(ParkingTicket t) {
            ParkingTicket p = new ParkingTicket();
            p.setTicketId(t.getTicketId());
            p.setLicensePlate(t.getLicensePlate());
            p.setSpotId(t.getSpotId());
            p.setEntryTime(t.getEntryTime());
            p.setExitTime(t.getExitTime());
            return p;
        }
    }

    // -----------------------------------------------------------------------
    // STRATEGY
    // -----------------------------------------------------------------------

    private interface SpotAssignmentStrategy {
        Optional<ParkingSpot> assignSpot(Vehicle v, List<ParkingSpot> spots);
    }

    private static class DefaultSpotAssignmentStrategy implements SpotAssignmentStrategy {

        @Override
        public Optional<ParkingSpot> assignSpot(Vehicle v, List<ParkingSpot> spots) {
            List<SpotType> preferred = preferredTypes(v.getVehicleType());

            for (SpotType type : preferred) {
                List<ParkingSpot> candidates = spots.stream()
                        .filter(s -> s.getSpotType() == type)
                        .sorted(Comparator.comparingInt(ParkingSpot::getFloor)
                                .thenComparing(ParkingSpot::getSpotId))
                        .collect(Collectors.toList());

                if (!candidates.isEmpty())
                    return Optional.of(candidates.get(0));
            }
            return Optional.empty();
        }

        private List<SpotType> preferredTypes(VehicleType t) {
            switch (t) {
                case MOTORCYCLE: return Arrays.asList(SpotType.COMPACT, SpotType.REGULAR, SpotType.LARGE);
                case CAR:        return Arrays.asList(SpotType.REGULAR, SpotType.LARGE);
                case TRUCK:      return Collections.singletonList(SpotType.LARGE);
            }
            return Collections.emptyList();
        }
    }
}
