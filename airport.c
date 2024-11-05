#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 30

typedef char String[40];

typedef struct {
    int hour;
    int minute;
} Schedule;

typedef struct {
    int dest_Priority;
    String dest_Name;
} Destination;

typedef struct {
    int flightCode;
    String aircraft;
    Schedule sched;
    Destination dest;
} Flight;

typedef struct {
    Flight data[MAX];
    int count;
} FlightList, PriorityQueue;


Schedule createSched(int hour, int minute);
Destination createDest(int priority, String destName);
Flight createFlight(int flightCode, String aircraft, Schedule sched, Destination dest);
void enqueueFlight(PriorityQueue *list, Flight f);
void dequeueFlight(PriorityQueue *list);
void displayFlight(Flight f);
void displayQueue(PriorityQueue list);

int main() {
    Destination NAIA = createDest(1, "Ninoy Aquino International Airport");
    Destination CIA = createDest(2, "Clark International Airport");
    Destination FBIA = createDest(2, "Francisco Bangoy International Airport");
    Destination ILOILO = createDest(2, "Iloilo International Airport");
    Destination Panglao = createDest(3, "Panglao International Airport");
    Destination Sibulan = createDest(3, "Sibulan Airport");
    Destination Siquijor = createDest(3, "Siquijor Airport");
    Destination Bicol = createDest(4, "Bicol International Airport");
    Destination Daniel = createDest(4, "Daniel Z. Romualdez Airport");
    Destination General = createDest(4, "General Santos International Airport");
    Destination Zamboanga = createDest(4, "Zamboanga International Airport");
    Destination Bantayan = createDest(5, "Bantayan Airport");
    Destination Bulan = createDest(5, "Bulan Airport");
    Destination Iba = createDest(5, "Iba Airport");
    Destination Hilongos = createDest(5, "Hilongos Airport");
    Destination Alto = createDest(6, "Alto Airfeild");
    Destination Amoroy = createDest(6, "Amoroy Airstrip");

    Flight f1 = createFlight(100, "Airbus", createSched(4,30), NAIA);
    Flight f2 = createFlight(101, "Boieng", createSched(7,00), FBIA);
    Flight f3 = createFlight(102, "Convair", createSched(12,15), Bicol);
    Flight f4 = createFlight(103, "Douglas", createSched(2,45), Zamboanga);
    Flight f5 = createFlight(104, "Airbus", createSched(6,20), Alto);
    Flight f6 = createFlight(105, "Convair", createSched(1,40), Bantayan);
    Flight f7 = createFlight(106, "Airbus", createSched(4,15), General);
    Flight f8 = createFlight(107, "Douglas", createSched(3,35), Iba);
    Flight f9 = createFlight(108, "Boieng", createSched(10,30), Panglao);
    Flight f10 = createFlight(109, "Airbus", createSched(9,00), Sibulan);
    Flight f11 = createFlight(110, "Boieng", createSched(7,30), Hilongos);

    PriorityQueue flightQueue;
    flightQueue.count = 0;

    enqueueFlight(&flightQueue, f1);
    enqueueFlight(&flightQueue, f2);
    enqueueFlight(&flightQueue, f3);
    enqueueFlight(&flightQueue, f4);
    enqueueFlight(&flightQueue, f5);
    enqueueFlight(&flightQueue, f6);
    enqueueFlight(&flightQueue, f7);
    enqueueFlight(&flightQueue, f8);
    enqueueFlight(&flightQueue, f9);
    enqueueFlight(&flightQueue, f10);
    enqueueFlight(&flightQueue, f11);

    displayQueue(flightQueue);

    return 0;
}


Schedule createSched(int hour, int minute) {
    Schedule s;

    s.hour = hour;
    s.minute = minute;

    return s;
}

Destination createDest(int priority, String destName) {
    Destination d;

    d.dest_Priority = priority;
    strcpy(d.dest_Name, destName);

    return d;
}

Flight createFlight(int flightCode, String aircraft, Schedule sched, Destination dest) {
    Flight f;

    f.flightCode = flightCode;
    strcpy(f.aircraft, aircraft);
    f.sched = sched;
    f.dest = dest;

    return f;
}

void displayQueue(PriorityQueue list) {
    if (list.count == 0) {
        printf("No flights in the queue.\n");
        return;
    }

    printf("Flight Code\t|\tAircraft\t|\tSchedule\t|\tDestination\t\t\t\t\t|\tPriority\n");
    printf("------------------------------------------------------------------------------------------------------------------------------------------\n");

    for (int i = 0; i < list.count; i++) {
        displayFlight(list.data[i]);
    }
}

void displayFlight(Flight f) {
    printf("%-12d\t|\t%-16s|\t%02d:%02d\t\t|\t%-32s\t\t|\t%d\n",
           f.flightCode, f.aircraft, f.sched.hour, f.sched.minute, f.dest.dest_Name, f.dest.dest_Priority);
}

void enqueueFlight(PriorityQueue *list, Flight f) {
    if (list->count >= MAX) {
        printf("Queue is full. Cannot add more flights.\n");
        return;
    }

    int i = list->count - 1;
    while (i >= 0 && list->data[i].dest.dest_Priority > f.dest.dest_Priority) {
        list->data[i + 1] = list->data[i];
        i--;
    }
    list->data[i + 1] = f;
    list->count++;
}

void dequeueFlight(PriorityQueue *list) {
    if (list->count == 0) {
        printf("Queue is empty. No flights to remove.\n");
        return;
    }

    printf("Dequeued Flight:\n");
    displayFlight(list->data[0]);

    for (int i = 1; i < list->count; i++) {
        list->data[i - 1] = list->data[i];
    }
    list->count--;
}

