package com.parkinglot;

import com.parkinglot.enums.*;
import com.parkinglot.models.*;
import com.parkinglot.service.ParkingLotManager;
import com.parkinglot.service.ParkingLotManagerInMemImpl;

import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import java.time.LocalDateTime;
import java.util.List;

import static org.junit.jupiter.api.Assertions.*;

public class ParkingLotManagerInMemImplTest {

    private ParkingLotManager manager;

    @BeforeEach
    void setup() {
        manager = new ParkingLotManagerInMemImpl();
    }

    @Test
    void testAddParkingSpot() {
        ParkingSpot spot = new ParkingSpot("S1", SpotType.COMPACT, 1);
        assertTrue(manager.addParkingSpot(spot));

        // Duplicate should fail
        assertFalse(manager.addParkingSpot(spot));
    }

    @Test
    void testRemoveParkingSpot() {
        ParkingSpot spot = new ParkingSpot("S1", SpotType.REGULAR, 2);
        manager.addParkingSpot(spot);

        assertTrue(manager.removeParkingSpot("S1"));
        assertFalse(manager.removeParkingSpot("S1")); // already removed
    }

    @Test
    void testGetAvailableSpotsByType() {
        ParkingSpot s1 = new ParkingSpot("S1", SpotType.COMPACT, 1);
        ParkingSpot s2 = new ParkingSpot("S2", SpotType.REGULAR, 2);
        manager.addParkingSpot(s1);
        manager.addParkingSpot(s2);

        List<ParkingSpot> compactSpots = manager.getAvailableSpotsByType(SpotType.COMPACT);
        assertEquals(1, compactSpots.size());
        assertEquals("S1", compactSpots.get(0).getSpotId());
    }

    @Test
    void testParkVehicleCompactFit() {
        manager.addParkingSpot(new ParkingSpot("C1", SpotType.COMPACT, 1));
        manager.addParkingSpot(new ParkingSpot("R1", SpotType.REGULAR, 2));

        Vehicle bike = new Vehicle("BIKE123", VehicleType.MOTORCYCLE, "John");

        ParkingTicket ticket = manager.parkVehicle(bike, LocalDateTime.now());

        assertNotNull(ticket);
        assertEquals("BIKE123", ticket.getLicensePlate());
        assertEquals("C1", ticket.getSpotId()); // should choose compact first

        ParkingSpot usedSpot = manager.getParkingSpot("C1");
        assertEquals(SpotStatus.OCCUPIED, usedSpot.getStatus());
    }

    @Test
    void testParkVehicleChoosesSmallestSpot() {
        manager.addParkingSpot(new ParkingSpot("L1", SpotType.LARGE, 3));
        manager.addParkingSpot(new ParkingSpot("R1", SpotType.REGULAR, 1));

        Vehicle car = new Vehicle("CAR123", VehicleType.CAR, "Alice");

        ParkingTicket ticket = manager.parkVehicle(car, LocalDateTime.now());

        assertEquals("R1", ticket.getSpotId()); // REGULAR preferred over LARGE
    }

    @Test
    void testParkFailsWhenNoSpotAvailable() {
        Vehicle truck = new Vehicle("T1", VehicleType.TRUCK, "Bob");
        ParkingTicket ticket = manager.parkVehicle(truck, LocalDateTime.now());

        assertNull(ticket); // No spots added → fail
    }

    @Test
    void testFindVehicleByLicense() {
        manager.addParkingSpot(new ParkingSpot("S1", SpotType.REGULAR, 1));

        Vehicle car = new Vehicle("ABC123", VehicleType.CAR, "Aman");
        ParkingTicket ticket = manager.parkVehicle(car, LocalDateTime.now());

        ParkingSpot spot = manager.findVehicleByLicense("ABC123");
        assertNotNull(spot);
        assertEquals("S1", spot.getSpotId());
    }

    @Test
    void testExitVehicle() {
        manager.addParkingSpot(new ParkingSpot("S1", SpotType.REGULAR, 1));

        Vehicle car = new Vehicle("XYZ999", VehicleType.CAR, "Ravi");
        ParkingTicket ticket = manager.parkVehicle(car, LocalDateTime.now());

        boolean result = manager.exitVehicle("XYZ999", LocalDateTime.now().plusHours(2));

        assertTrue(result);

        ParkingSpot spot = manager.getParkingSpot("S1");
        assertEquals(SpotStatus.AVAILABLE, spot.getStatus());
        assertNull(spot.getParkedVehicleLicense());
    }

    @Test
    void testExitVehicleFailsIfNotParked() {
        assertFalse(manager.exitVehicle("NOPE123", LocalDateTime.now()));
    }
}
