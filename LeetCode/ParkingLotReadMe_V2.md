# Parking Lot System

This project is a basic in-memory parking lot system. It handles parking spots, vehicles, and tickets without using any external storage. The code is kept straightforward so it is easy to follow and extend if needed.

## Features

- Add and remove parking spots
- Park a vehicle and create a parking ticket
- Exit a vehicle and free the spot
- Find which spot a vehicle is parked in
- Get a list of available spots by type

## How It Works

All main actions are handled in `ParkingLotManagerInMemImpl`.  
The class uses small in-memory repositories to store parking spots and tickets.  
A simple strategy is used to select a parking spot:

1. Choose the smallest spot type that fits the vehicle  
2. Prefer lower floors  
3. If more than one spot matches, pick the one with the lower spot ID  

These rules help the system stay consistent and predictable.

## Models

The project includes three model classes:
- ParkingSpot
- ParkingTicket
- Vehicle

These classes only hold data and do not contain logic.

## Unit Tests

JUnit tests are provided to check:
- Adding and removing spots  
- Parking and exiting vehicles  
- Spot selection logic  
- Error cases like trying to park when no spots are available  

## Notes

This system runs fully in memory and does not save any data once the program stops.  
It is meant to show clean and simple design rather than full production features.
