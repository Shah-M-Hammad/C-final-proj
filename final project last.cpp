#include <iostream>
#include <fstream>
#include <ctime>

using namespace std;

int main() {
    int car = 0, bike = 0, truck = 0 ,pcar = 10 ,pbike = 10,ptruck = 10;
    string veh, pla, plate;

    ifstream out("parked.txt");

    while (out >> veh >> pla) {
        if (veh == "Car")
            car++;
        else if (veh == "Bike")
            bike++;
        else if (veh == "Truck")
            truck++;
    }
    out.close();

    cout << "\n\t\tV E C H I L E  P A R K I N G" << endl
         << endl;
    int enter;

    while (true) {
        cout << "Press 1 to enter car" << endl;
        cout << "Press 2 to enter bike" << endl;
        cout << "Press 3 to enter truck" << endl;
        cout << "Press 4 to show the Parked record" << endl;
        cout << "Press 5 to Parked Out" << endl;
        cout << "Press 6 to exit" << endl;
        cin >> enter;

        if (enter == 1) {
            if (car <= pcar) {
                cout << "Enter your vehicle number plate: ";
                cin >> plate;

                time_t current_time = time(NULL);
                struct tm* timeinfo = localtime(&current_time);
                char time_buffer[9];
                strftime(time_buffer, sizeof(time_buffer), "%H:%M:%S", timeinfo);

                ofstream in("parked.txt", ios::app);
                in << "Car" << " " << plate << " " << time_buffer << endl;
                in.close();

                cout << "Congrats! you can now park the Car" << endl;
                car++;
            } else {
                cout << "Parking Is full\n";
            }
        } else if (enter == 2) {
            if (bike <= pbike) {
                cout << "Enter your vehicle number plate: ";
                cin >> plate;
                time_t current_time = time(NULL);
                struct tm* timeinfo = localtime(&current_time);
                char time_buffer[9];
                strftime(time_buffer, sizeof(time_buffer), "%H:%M:%S", timeinfo);
                
                ofstream in("parked.txt", ios::app);
                in << "Bike" << " " << plate << " " << time_buffer<< endl;
                in.close();

                cout << "Congrats! you can now park the Bike" << endl;
                bike++;
            } else {
                cout << "Parking Is full";
            }
        } else if (enter == 3) {
            if (truck <= ptruck) {
                cout << "Enter your vehicle number plate: ";
                cin >> plate;
                time_t current_time = time(NULL);
                struct tm* timeinfo = localtime(&current_time);
                char time_buffer[9];
                strftime(time_buffer, sizeof(time_buffer), "%H:%M:%S", timeinfo);
                ofstream in("parked.txt", ios::app);
                in << "Truck" << " " << plate <<" " << time_buffer<< endl;
                in.close();

                cout << "Congrats! you can now park the Truck" << endl;
                truck++;
            } else {
                cout << "Parking Is full";
            }
        } else if (enter == 4) {
            cout << "\n---Data---" << endl << endl;
            cout << "Vehicle  NumberPlate \t Time In\n";

            ifstream out("parked.txt");
            string timein,timeout;
            while (out >> veh >> pla>>timein) {
                cout << veh << " \t " << pla<<" \t "<<timein<< endl;
            }
            out.close();

            cout << "\n\n";
        } else if (enter == 5) {
            cout << "Enter your vehicle number plate: ";
            cin >> plate;

            ifstream in("parked.txt");
            ofstream temp("temp.txt");

            bool vehicleFound = false;

            if (in.is_open() && temp.is_open()) {
                string line;
                while (getline(in, line)) {
                    size_t found = line.find(plate);
                    if (found != string::npos) {
                        time_t current_time = time(NULL);
                        struct tm* timeinfo = localtime(&current_time);
                        char time_buffer[9];
                        strftime(time_buffer, sizeof(time_buffer), "%H:%M:%S", timeinfo);
                        temp << line << " " << time_buffer << endl;
                        cout << "Vehicle " << plate << " was parked." << endl;
                        cout << "Time out: " << time_buffer << endl;
                        vehicleFound = true;
                    } else {
                        temp << line << endl;
                    }
                }
                in.close();
                temp.close();
                remove("parked.txt");
                rename("temp.txt", "parked.txt");
            } else {
                cout << "Unable to open the file." << endl;
            }

            if (!vehicleFound) {
                cout << "Vehicle " << plate << " not found in the parking record." << endl;
            }
        } else if (enter == 6) {
            exit(0);
        }
    }
    return 0;
}

