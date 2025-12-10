# Parking Lot System

This project is a simple in-memory parking lot system. It lets you add spots, park vehicles, exit vehicles, and check which spots are available. The goal is to keep the code easy to read and understand.

## Features

- Add and remove parking spots
- Park a vehicle and create a ticket
- Exit a vehicle and free the spot
- Find a vehicle by license plate
- Get available spots by type

## How It Works

The main logic is in `ParkingLotManagerInMemImpl`.  
It uses small in-memory classes to store parking spots and tickets.  
A simple rule is used to choose the best spot for a vehicle:

1. Pick the smallest spot that fits the vehicle
2. Prefer lower floors
3. If still tied, pick by spot ID

## Models

The project includes:
- ParkingSpot
- ParkingTicket
- Vehicle

These are basic classes that only store data.

## Tests

JUnit tests are included to check parking, exiting, and spot selection.

## Notes

Everything runs in memory and nothing is saved permanently.
