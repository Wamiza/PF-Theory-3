#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Weather {
    float temperature;  
    float rainfall;     
    float windSpeed;    
};

struct Crop {
    char type[50];          
    char growthStage[50];   
    float expectedYield;    
    struct Weather *forecast;  
};

struct Equipment {
    char name[50];        
    int operationalStatus; 
    float fuelLevel;        
    char schedule[100];     
};

struct Sensor {
    float soilNutrients;    
    float soilPh;          
    int pestActivity;       
};

struct Field {
    float gpsCoordinates[2];  
    float soilHealth;         
    float moistureLevel;     
    struct Crop *crops;       
    struct Equipment *equipment; 
    struct Sensor *sensors;   
    int numCrops;             
    int numEquipment;         
    int numSensors;           
};

struct RegionalHub {
    char hubName[50];         
    struct Field **fields;    
    int numFields;            
    float totalYield;         
};

struct CentralServer {
    struct RegionalHub **regionalHubs;  
    int numHubs;             
};

void initializeWeather(struct Weather *weather);
void initializeCrop(struct Crop *crop);
void initializeEquipment(struct Equipment *equipment);
void initializeSensor(struct Sensor *sensor);
void initializeField(struct Field *field, int numCrops, int numEquipment, int numSensors);
void initializeRegionalHub(struct RegionalHub *hub, int numFields);
void initializeCentralServer(struct CentralServer *server, int numHubs);
void displayFieldData(struct Field *field);
void displayRegionalHubData(struct RegionalHub *hub);
void displayCentralServerData(struct CentralServer *server);
void freeMemory(struct CentralServer *server);
void inputCropData(struct Crop *crop);
void inputEquipmentData(struct Equipment *equipment);
void inputSensorData(struct Sensor *sensor);
void inputFieldData(struct Field *field);

int main() {
    struct CentralServer server;
    initializeCentralServer(&server, 1);

    struct Field field;
    inputFieldData(&field);

    for (int i = 0; i < field.numCrops; i++) {
        inputCropData(&field.crops[i]);
    }

    server.regionalHubs[0]->fields[0] = &field;

    displayCentralServerData(&server);
    displayRegionalHubData(server.regionalHubs[0]);
    displayFieldData(&field);

    freeMemory(&server);

    return 0;
}

void initializeWeather(struct Weather *weather) {
    printf("Enter temperature (Celsius): ");
    scanf("%f", &weather->temperature);
    printf("Enter rainfall (mm): ");
    scanf("%f", &weather->rainfall);
    printf("Enter wind speed (m/s): ");
    scanf("%f", &weather->windSpeed);
}

void inputCropData(struct Crop *crop) {
    printf("Enter crop type (e.g., Wheat, Corn): ");
    scanf("%s", crop->type);
    printf("Enter growth stage (e.g., Germination, Maturity): ");
    scanf("%s", crop->growthStage);
    printf("Enter expected yield (kg/hectare): ");
    scanf("%f", &crop->expectedYield);

    crop->forecast = (struct Weather *)malloc(sizeof(struct Weather));
    initializeWeather(crop->forecast);
}

void inputEquipmentData(struct Equipment *equipment) {
    printf("Enter equipment name (e.g., Tractor, Irrigation System): ");
    scanf("%s", equipment->name);
    printf("Enter operational status (1 for active, 0 for inactive): ");
    scanf("%d", &equipment->operationalStatus);
    printf("Enter fuel level (liters): ");
    scanf("%f", &equipment->fuelLevel);
    printf("Enter schedule (e.g., daily, weekly): ");
    scanf("%s", equipment->schedule);
}

void inputSensorData(struct Sensor *sensor) {
    printf("Enter soil nutrients level: ");
    scanf("%f", &sensor->soilNutrients);
    printf("Enter soil pH level: ");
    scanf("%f", &sensor->soilPh);
    printf("Enter pest activity (0 for low, 1 for moderate, 2 for high): ");
    scanf("%d", &sensor->pestActivity);
}

void inputFieldData(struct Field *field) {
    printf("Enter GPS coordinates (latitude, longitude): ");
    scanf("%f %f", &field->gpsCoordinates[0], &field->gpsCoordinates[1]);
    printf("Enter soil health (1-10): ");
    scanf("%f", &field->soilHealth);
    printf("Enter moisture level (0-100): ");
    scanf("%f", &field->moistureLevel);

    printf("Enter number of crops: ");
    scanf("%d", &field->numCrops);
    printf("Enter number of equipment: ");
    scanf("%d", &field->numEquipment);
    printf("Enter number of sensors: ");
    scanf("%d", &field->numSensors);

    field->crops = (struct Crop *)malloc(field->numCrops * sizeof(struct Crop));
    field->equipment = (struct Equipment *)malloc(field->numEquipment * sizeof(struct Equipment));
    field->sensors = (struct Sensor *)malloc(field->numSensors * sizeof(struct Sensor));

    for (int i = 0; i < field->numCrops; i++) {
        inputCropData(&field->crops[i]);
    }
    for (int i = 0; i < field->numEquipment; i++) {
        inputEquipmentData(&field->equipment[i]);
    }
    for (int i = 0; i < field->numSensors; i++) {
        inputSensorData(&field->sensors[i]);
    }
}

void displayFieldData(struct Field *field) {
    printf("\nField Data:\n");
    printf("GPS Coordinates: (%.2f, %.2f)\n", field->gpsCoordinates[0], field->gpsCoordinates[1]);
    printf("Soil Health: %.2f\n", field->soilHealth);
    printf("Moisture Level: %.2f\n", field->moistureLevel);

    for (int i = 0; i < field->numCrops; i++) {
        printf("Crop %d: %s (Growth Stage: %s, Expected Yield: %.2f)\n", 
            i + 1, field->crops[i].type, field->crops[i].growthStage, field->crops[i].expectedYield);
                printf("Weather Forecast: Temperature %.2f°C, Rainfall %.2f mm, Wind Speed %.2f m/s\n", 
            field->crops[i].forecast->temperature, field->crops[i].forecast->rainfall, field->crops[i].forecast->windSpeed);
}

    for (int i = 0; i < field->numEquipment; i++) {
        printf("Equipment %d: %s (Operational Status: %d, Fuel Level: %.2f liters, Schedule: %s)\n", 
            i + 1, field->equipment[i].name, field->equipment[i].operationalStatus, field->equipment[i].fuelLevel, field->equipment[i].schedule);
    }

    for (int i = 0; i < field->numSensors; i++) {
        printf("Sensor %d: Soil Nutrients: %.2f, Soil pH: %.2f, Pest Activity: %d\n", 
            i + 1, field->sensors[i].soilNutrients, field->sensors[i].soilPh, field->sensors[i].pestActivity);
    }
}

void displayRegionalHubData(struct RegionalHub *hub) {
    printf("\nRegional Hub: %s\n", hub->hubName);
    printf("Total Yield Prediction: %.2f kg/hectare\n", hub->totalYield);

    for (int i = 0; i < hub->numFields; i++) {
        displayFieldData(hub->fields[i]);
    }
}

void displayCentralServerData(struct CentralServer *server) {
    printf("\nCentral Server Data:\n");
    printf("Number of Regional Hubs: %d\n", server->numHubs);

    for (int i = 0; i < server->numHubs; i++) {
        displayRegionalHubData(server->regionalHubs[i]);
    }
}

void freeMemory(struct CentralServer *server) {
    for (int i = 0; i < server->numHubs; i++) {
        struct RegionalHub *hub = server->regionalHubs[i];

        for (int j = 0; j < hub->numFields; j++) {
            struct Field *field = hub->fields[j];

            for (int k = 0; k < field->numCrops; k++) {
                free(field->crops[k].forecast);  
            }
            free(field->crops);
            free(field->equipment);
            free(field->sensors);
            free(field);
        }

        free(hub->fields);
        free(hub);
    }
    free(server->regionalHubs);
}

