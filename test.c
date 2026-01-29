#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

// Constants
#define MAX_USERS 100
#define MAX_VEHICLES 100
#define MAX_HISTORY 1000
#define USER_FILE "users.dat"
#define VEHICLE_FILE "vehicles.dat"
#define HISTORY_FILE "history.dat"

// Function prototypes
void print_banner(const char *banner);
void system_cleaner();
void sign_up();
int log_in();
void user_menu();
void add_vehicle();
void checkout_vehicle();
void log_out();
void view_my_vehicles();
void save_data();
void load_data();
void edit_profile();
void view_parking_history();
void search_vehicle();
void extend_parking();

// Data structures
typedef struct
{
    char username[50];
    char password[50];
    char email[100]; // New field for user email
    char phone[15];  // New field for user phone number
} 
User;

typedef struct
{
    char vehicle_type[20];
    char license_plate[15];
    char owner_name[50];
    time_t entry_time;
    time_t exit_time;
    float cost;
    char payment_method[20];
    int is_parked;
} 
Vehicle;

typedef struct
{
    char license_plate[15];
    time_t entry_time;
    time_t exit_time;
    float cost;
} 
HistoryEntry;

// Global variables
User users[MAX_USERS];
Vehicle vehicles[MAX_VEHICLES];
HistoryEntry history[MAX_HISTORY];
int user_count = 0;
int vehicle_count = 0;
int history_count = 0;
char current_user[50] = "";

// Parking rates
const float CAR_RATE = 50.0;
const float BIKE_RATE = 30.0;
const float TRUCK_RATE = 100.0;

int main()
//////11111111111
{
    load_data(); // Load existing data at startup

    while (1)
    {
        system_cleaner();
        print_banner("Parking System Main Menu");

        printf("1. Sign Up\n");
        printf("2. Log In\n");
        printf("3. Exit\n");
        printf("Choose an option: ");

        int choice;
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            sign_up();
            break;

        case 2:
            if (log_in())
            {
                user_menu();
            }
            break;

        case 3:
            save_data(); // Save data before exiting
            printf("\nExiting system...\n");
            exit(0);
        default:
            printf("Invalid choice!\n");
        }
    }
    return 0;
}

//////////11111111111
void save_data()
{
    FILE *file;

    // Save users
    file = fopen(USER_FILE, "wb");
    if (file != NULL)
    {
        fwrite(&user_count, sizeof(int), 1, file);
        fwrite(users, sizeof(User), user_count, file);
        fclose(file);
    }

    // Save vehicles
    file = fopen(VEHICLE_FILE, "wb");
    if (file != NULL)
    {
        fwrite(&vehicle_count, sizeof(int), 1, file);
        fwrite(vehicles, sizeof(Vehicle), vehicle_count, file);
        fclose(file);
    }

    // Save history
    file = fopen(HISTORY_FILE, "wb");
    if (file != NULL)
    {
        fwrite(&history_count, sizeof(int), 1, file);
        fwrite(history, sizeof(HistoryEntry), history_count, file);
        fclose(file);
    }
}

//////////111111111111
void load_data()
{
    FILE *file;

    // Load users
    file = fopen(USER_FILE, "rb");
    if (file != NULL)
    {
        fread(&user_count, sizeof(int), 1, file);
        fread(users, sizeof(User), user_count, file);
        fclose(file);
    }

    // Load vehicles
    file = fopen(VEHICLE_FILE, "rb");
    if (file != NULL)
    {
        fread(&vehicle_count, sizeof(int), 1, file);
        fread(vehicles, sizeof(Vehicle), vehicle_count, file);
        fclose(file);
    }

    // Load history
    file = fopen(HISTORY_FILE, "rb");
    if (file != NULL)
    {
        fread(&history_count, sizeof(int), 1, file);
        fread(history, sizeof(HistoryEntry), history_count, file);
        fclose(file);
    }
}

///////1111111111

void print_banner(const char *banner)
{
    printf("\n==================== %s ====================\n", banner);
}

////////11111111111
void system_cleaner()
{
    printf("\nPress Enter to continue...");
    getchar();
    getchar();
    system("clear || cls");
}

/////////222222222222
void sign_up()
{
    system_cleaner();
    print_banner("User  Registration");

    if (user_count >= MAX_USERS)
    {
        printf("User  limit reached!\n");
        return;
    }

    printf("Enter username: ");
    scanf("%s", users[user_count].username);

    // Check if username exists
    for (int i = 0; i < user_count; i++)
    {
        if (strcmp(users[i].username, users[user_count].username) == 0)
        {
            printf("Username already exists!\n");
            return;
        }
    }

    printf("Enter password: ");
    scanf("%s", users[user_count].password);

    // New fields for email and phone
    printf("Enter email: ");
    scanf("%s", users[user_count].email);

    printf("Enter phone number: ");
    scanf("%s", users[user_count].phone);

    user_count++;
    save_data(); // Save after registration
    printf("\nRegistration successful! You can now login.\n");
}

////////22222222222222
int log_in()
{
    system_cleaner();
    print_banner("User  Login");

    char username[50], password[50];
    printf("Enter username: ");
    scanf("%s", username);
    
    printf("Enter password: ");
    scanf("%s", password);

    for (int i = 0; i < user_count; i++)
    {
        if (strcmp(users[i].username, username) == 0 &&
            strcmp(users[i].password, password) == 0)
        {
            strcpy(current_user, username);
            return 1;
        }
    }

    printf("Invalid credentials!\n");
    return 0;
}

//////222222222
void user_menu()
{
    while (1)
    {
        system_cleaner();
        print_banner("User  Dashboard");
        printf("Logged in as: %s\n\n", current_user);
        printf("1. Add Vehicle\n");
        printf("2. View My Vehicles\n");
        printf("3. Checkout Vehicle\n");
        printf("4. Edit Profile\n");
        printf("5. View Parking History\n");
        printf("6. Search Vehicle\n");
        printf("7. Extend Parking\n");
        printf("8. Logout\n");
        printf("Choose an option: ");

        int choice;
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            add_vehicle();
            save_data(); // Save after adding vehicle
            break;

        case 2:
            view_my_vehicles();
            break;

        case 3:
            checkout_vehicle();
            save_data(); // Save after checkout
            break;

        case 4:
            edit_profile();
            save_data(); // Save after editing profile
            break;

        case 5:
            view_parking_history();
            break;

        case 6:
            search_vehicle();
            break;

        case 7:
            extend_parking();
            save_data();
            break;

        case 8:
            log_out();
            return;

        default:
            printf("Invalid choice!\n");
        }
    }
}

////////2222222222
void add_vehicle()
{
    system_cleaner();
    print_banner("Add New Vehicle");

    if (vehicle_count >= MAX_VEHICLES)
    {
        printf("Parking lot is full!\n");
        return;
    }

    printf("Enter vehicle type (car/bike/truck): ");
    scanf("%s", vehicles[vehicle_count].vehicle_type);

    printf("Enter license plate: ");
    scanf("%s", vehicles[vehicle_count].license_plate);

    // Check if vehicle already exists
    for (int i = 0; i < vehicle_count; i++)
    {
        if (strcmp(vehicles[i].license_plate, vehicles[vehicle_count].license_plate) == 0 &&
            vehicles[i].is_parked)
        {
            printf("Vehicle already parked!\n");
            return;
        }
    }

    // Set owner name to current user
    strcpy(vehicles[vehicle_count].owner_name, current_user);

    time(&vehicles[vehicle_count].entry_time);
    vehicles[vehicle_count].is_parked = 1;

    printf("\nVehicle added successfully!\n");
    printf("Entry Time: %s", ctime(&vehicles[vehicle_count].entry_time));

    vehicle_count++;
}

//////2222222222
void view_my_vehicles()
{
    system_cleaner();
    print_banner("My Parked Vehicles");

    printf("%-15s %-10s %-20s %-30s\n", "License Plate", "Type", "Owner", "Entry Time");
    printf("------------------------------------------------------------\n");

    int found = 0;
    for (int i = 0; i < vehicle_count; i++)
    {
        if (vehicles[i].is_parked && strcmp(vehicles[i].owner_name, current_user) == 0)
        {
            printf("%-15s %-10s %-20s %-30s",
                   vehicles[i].license_plate,
                   vehicles[i].vehicle_type,
                   vehicles[i].owner_name,
                   ctime(&vehicles[i].entry_time));
            found = 1;
        }
    }

    if (!found)
    {
        printf("You have no parked vehicles!\n");
    }
}

////////333333333333
void checkout_vehicle()
{
    system_cleaner();
    print_banner("Vehicle Checkout");

    char license_plate[15];
    printf("Enter license plate: ");
    scanf("%s", license_plate);

    for (int i = 0; i < vehicle_count; i++)
    {
        if (strcmp(vehicles[i].license_plate, license_plate) == 0 &&
            vehicles[i].is_parked &&
            strcmp(vehicles[i].owner_name, current_user) == 0)
        {

            time(&vehicles[i].exit_time);
            vehicles[i].is_parked = 0;

            // Calculate cost based on parking duration
            double seconds = difftime(vehicles[i].exit_time, vehicles[i].entry_time);
            float hours = seconds / 3600;

            if (strcmp(vehicles[i].vehicle_type, "car") == 0)
            {
                vehicles[i].cost = hours * CAR_RATE;
            }

            else if (strcmp(vehicles[i].vehicle_type, "bike") == 0)
            {
                vehicles[i].cost = hours * BIKE_RATE;
            }

            else if (strcmp(vehicles[i].vehicle_type, "truck") == 0)
            {
                vehicles[i].cost = hours * TRUCK_RATE;
            }

            else
            {
                vehicles[i].cost = hours * 40.0; // Default rate
            }

            printf("\nVehicle Checkout Details\n");
            printf("-----------------------------\n");
            printf("Type: %s\n", vehicles[i].vehicle_type);
            printf("License Plate: %s\n", vehicles[i].license_plate);
            printf("Owner: %s\n", vehicles[i].owner_name);
            printf("Entry Time: %s", ctime(&vehicles[i].entry_time));
            printf("Exit Time: %s", ctime(&vehicles[i].exit_time));
            printf("Parking Duration: %.2f hours\n", hours);
            printf("Total Cost: $%.2f\n", vehicles[i].cost);

            // Add to history
            if (history_count < MAX_HISTORY)
            {
                strcpy(history[history_count].license_plate, vehicles[i].license_plate);
                history[history_count].entry_time = vehicles[i].entry_time;
                history[history_count].exit_time = vehicles[i].exit_time;
                history[history_count].cost = vehicles[i].cost;
                history_count++;
            }

            return;
        }
    }

    printf("Vehicle not found, already checked out, or doesn't belong to you!\n");
}
/////////33333333333
void edit_profile()
{
    system_cleaner();
    print_banner("Edit Profile");

    for (int i = 0; i < user_count; i++)
    {
        if (strcmp(users[i].username, current_user) == 0)
        {
            printf("Current Email: %s\n", users[i].email);
            printf("Current Phone: %s\n", users[i].phone);
            printf("Enter new email (or press Enter to keep current): ");
            
            char new_email[100];
            fgets(new_email, sizeof(new_email), stdin);
            new_email[strcspn(new_email, "\n")] = 0; // Remove newline

            if (strlen(new_email) > 0)
            {
                strcpy(users[i].email, new_email);
            }

            printf("Enter new phone number (or press Enter to keep current): ");
            char new_phone[15];
            fgets(new_phone, sizeof(new_phone), stdin);
            new_phone[strcspn(new_phone, "\n")] = 0; // Remove newline

            if (strlen(new_phone) > 0)
            {
                strcpy(users[i].phone, new_phone);
            }

            printf("Profile updated successfully!\n");
            return;
        }
    }
}

///////33333333333
void view_parking_history()
{
    system_cleaner();
    print_banner("Parking History");

    printf("%-15s %-30s %-30s %-10s\n", "License Plate", "Entry Time", "Exit Time", "Cost");
    printf("------------------------------------------------------------\n");

    int found = 0;
    for (int i = 0; i < history_count; i++)
    {
        if (strcmp(history[i].license_plate, current_user) == 0)
        {
            printf("%-15s %-30s %-30s $%.2f\n",
                   history[i].license_plate,
                   ctime(&history[i].entry_time),
                   ctime(&history[i].exit_time),
                   history[i].cost);
            found = 1;
        }
    }

    if (!found)
    {
        printf("No parking history found!\n");
    }
}

///////33333333333
void search_vehicle()
{
    system_cleaner();
    print_banner("Search Vehicle");

    char license_plate[15];
    printf("Enter license plate to search: ");
    scanf("%s", license_plate);

    for (int i = 0; i < vehicle_count; i++)
    {
        if (strcmp(vehicles[i].license_plate, license_plate) == 0)
        {
            printf("Vehicle found!\n");
            printf("Type: %s\n", vehicles[i].vehicle_type);
            printf("Owner: %s\n", vehicles[i].owner_name);
            printf("Entry Time: %s", ctime(&vehicles[i].entry_time));
            printf("Is Parked: %s\n", vehicles[i].is_parked ? "Yes" : "No");
        return;
        }
    }

    printf("Vehicle not found!\n");
}

/////3333333333
void extend_parking()
{
    system_cleaner();
    print_banner("Extend Parking");

    char license_plate[15];
    printf("Enter license plate to extend parking: ");
    scanf("%s", license_plate);

    for (int i = 0; i < vehicle_count; i++)
    {
        if (strcmp(vehicles[i].license_plate, license_plate) == 0 && vehicles[i].is_parked)
        {
            printf("Current Entry Time: %s", 
            ctime(&vehicles[i].entry_time));
            printf("Current Parking Duration: %.2f hours\n",
            difftime(time(NULL), vehicles[i].entry_time) / 3600);

            // Extend parking by a fixed amount of time (e.g., 2 hours)
            vehicles[i].entry_time -= 2 * 3600; // Extend by 2 hours
            printf("Parking extended by 2 hours!\n");
            return;
        }
    }

    printf("Vehicle not found or not parked!\n");
}

void log_out()
{
    strcpy(current_user, "");
    printf("\nLogged out successfully!\n");
}
