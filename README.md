# Parking Management System

## Project Description

The Parking Management System is a C-based console application designed to manage parking operations efficiently. It allows users to register, log in, add vehicles to the parking lot, view their parked vehicles, checkout vehicles, extend parking time, and track parking history. This system uses file-based storage to ensure data persistence across sessions.

It is suitable for small parking lots and serves as a learning project to demonstrate user management, file I/O, and time-based calculations in C.

---

## Key Features

### User Management
- Sign Up with username, password, email, and phone number.
- Log In using credentials.
- Edit profile (email and phone).
- Log Out functionality.

### Vehicle Management
- Add a vehicle (Car, Bike, Truck).
- View all currently parked vehicles for the logged-in user.
- Checkout vehicles with cost calculation based on parking duration.
- Extend parking time for vehicles already parked.

### Parking History
- Track and view past parking entries with cost.
- Provides license plate, entry and exit time, and total cost.

### Vehicle Search
- Search for any vehicle by license plate.
- Shows owner, type, entry time, and current parking status.

### Data Persistence
- User, vehicle, and history data are saved in binary files:
  - `users.dat`
  - `vehicles.dat`
  - `history.dat`
- Data is loaded automatically when the system starts.

---

## Parking Rates

| Vehicle Type | Rate per Hour |
|--------------|---------------|
| Car          | $50           |
| Bike         | $30           |
| Truck        | $100          |
| Other        | $40           |

Rates are used to calculate the parking cost during checkout.

---

## Technical Details

- **Language:** C
- **Platform:** Console-based, cross-platform (Windows/Linux)
- **Storage:** Binary files for persistent data
- **Limitations:**
  - Maximum 100 users.
  - Maximum 100 vehicles.
  - Maximum 1000 parking history entries.

---

## Usage Workflow

1. Launch the program.
2. From the main menu, choose:
   - Sign Up
   - Log In
   - Exit
3. After logging in, access the user dashboard to:
   - Add a vehicle to the parking lot.
   - View all your parked vehicles.
   - Checkout a vehicle and view total cost.
   - Edit your profile.
   - View parking history.
   - Search for a vehicle.
   - Extend parking time.
   - Log out.

---

## Future Improvements

- Add a graphical user interface (GUI).
- Integrate real-time payment systems.
- Admin dashboard for managing multiple parking lots.
- Generate reports and analytics for parking usage.

---

## Author

**Tasnim Nayeem**
