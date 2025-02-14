// Online C++ compiler to run C++ program online
#include <iostream>
#include <stdint.h>

void printPacket(uint8_t* packet, short length){
    printf("[");
    for(int i = 0; i < length; i ++){
        printf("0x%02X,", packet[i]);
    }
    printf("]\n");
}

class CAN{
private:
    uint8_t stored[8] = {0,0,0,0,0,0,0,0};
    short id;
public: 
    CAN(){}
    
    void sendPacket(short id, uint8_t* packet, short length){
        printf("You sent this packet: [id: 0x%04X]",id);
        printPacket(packet, length);
        if(!(id ^ 0x23E1 ^ 0x221E)){ //convoluted for no reason lol
            printf("Motor successfully recieved angle: %d | velocity: %d | torque: %d | temperature: %d\n", packet[0] << 8 | packet[1], (int16_t)(packet[2] << 8 | packet[3]), (int16_t)(packet[4] << 8 | packet[5]), packet[6]);
            this->id = id;
            int a = rand() % 8192;
            int v = (rand() % 16000) - 8000;
            int c = (rand() % 300) - 150;
            int t = (rand() % 30) + 60;
            stored[0] = (uint8_t)(a >> 8);
            stored[1] = (uint8_t)(a);
            stored[2] = (uint8_t)(v >> 8);
            stored[3] = (uint8_t)(v);
            stored[4] = (uint8_t)(c >> 8);
            stored[5] = (uint8_t)(c);
            stored[6] = (uint8_t)(t);
            stored[7] = 0x00;
            //printPacket(stored, 8);
        }
    }
    
    void readPacket(short* id, uint8_t* packet, short* length){
        *length = 8;
        *id = this->id;
        std::copy(stored, stored + 8, packet);
        printf("You recieved this packet: [id: 0x%04X]",this->id);
        
        printPacket(packet, 8);
    }
};

//TOUCH NOTHING ABOVE THIS

int main() {
    srand(2);
    CAN canbus;

    int16_t angle = 1750;
    int16_t velocity = 2000;
    int16_t torque = 400;
    int8_t temperature = 20;

    uint8_t data_send[8] = {0};
    short len_send = 8;
    short id_send = 0x1FF;

    // Encoding the data
    data_send[0] = (angle >> 8) & 0xFF;
    data_send[1] = angle & 0xFF;
    data_send[2] = (velocity >> 8) & 0xFF;
    data_send[3] = velocity & 0xFF;
    data_send[4] = (torque >> 8) & 0xFF;
    data_send[5] = torque & 0xFF;
    data_send[6] = temperature;
    data_send[7] = 0x00;

    canbus.sendPacket(id_send, data_send, len_send);

    uint8_t data_recv[8] = {0};
    short len_recv;
    short id_recv;

    canbus.readPacket(&id_recv, data_recv, &len_recv);

    // Decoding the received data
    int16_t decoded_angle = (data_recv[0] << 8) | data_recv[1];
    int16_t decoded_velocity = (int16_t)((data_recv[2] << 8) | data_recv[3]);
    int16_t decoded_torque = (int16_t)((data_recv[4] << 8) | data_recv[5]);
    int8_t decoded_temperature = data_recv[6];

    printf("Decoded Values:\n");
    printf("Angle: %d\n", decoded_angle);
    printf("Velocity: %d\n", decoded_velocity);
    printf("Torque: %d\n", decoded_torque);
    printf("Temperature: %d\n", decoded_temperature);
    
    return 0;
}
