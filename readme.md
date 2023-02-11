<!-- @format -->

# SmartHouse Server

_Under development_

SmartHouse Server is a typical HTTP server, but for handling smart devices and sensors. Easy to install and maintain, you can register your devices, set statuses for them, etc.

## Installation process

You need following programs be installed:

- Cmake
- Conan pakage manager

Linux:

- `./unix-install.sh` from root folder

From Windows:

- `./windows-install.cmd`

## API Documentation

- device
_accept: GET, PUT, POST, DELETE, OPTIONS_

id - get device by id
name - name of device
status - status of device by which you can control behavior of device

### Device list:
- smokeSensor
    possible status: 
        - smokeNOTDetected 
        - smokeDetected - to activate event with smoke
- waterSensor
    possible status: 
        - floodNOTDetected 
        - floddDetected - to activate event with flood
- window
    possible status: 
        - open 
        - closed
- light
    possible status: 
        - off 
        - on
- smartDevice
    possible status: 
        - off 
        - on
- oven
    possible status: 
        - off 
        - on
- tap
    possible status: 
        - open 
        - closed
- garageDoors
    possible status: 
        - open 
        - closed


### Exampple:

### GET /device
_returns all devices_

### GET /device?id=0
_returns device with id 0_
`
{
    "id": "0",
    "name": "smokeSensor",
    "status": "smokeNOTDetected"
}
`
### PUT /device
_you can update any field of device except id_
`
{
    "status": "smokeDetected"
}
`

### GET /logs
_returns all type of logs_
_use type parameter for filtering specific logs_
Logs types:
- information
- error
- warning

### Managing server
_we are using small python server for managin main server_

Use port 8008 to manage main server
start - start main server
stop - stop main server
restore - restore db

