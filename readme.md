<!-- @format -->

# SmartHouse Server

_v 1.2_

SmartHouse Server is a typical HTTP server, but for handling smart devices and sensors. Easy to install and maintain, you can register your devices, set statuses for them, etc.

Default ports:
- `8080` for main server
- `8008` for startup server

## Installation process

You need following programs be installed:

- Cmake
- Conan pakage manager

### Linux:

- `./unix-install.sh` from root folder

### From Windows:

- `./windows-install.cmd`

_If you want to manage smarthouse server remotely you also need pyton3:_

-  `python3 ./startupServer.py`

## API Documentation

- device
  _accept: GET, PUT, POST, DELETE, OPTIONS_

id - get device by id
name - name of device
status - status of device by which you can control behavior of device

### Device list:

- smokeSensor
  possible status: _smokeNOTDetected, smokeDetected_ to activate event with smoke
- waterSensor
  possible status: _floodNOTDetected. floddDetected_ to activate event with flood
- window
  possible status: _open, closed_
- light
  possible status: _off, on_
- smartDevice
  possible status: _off, on_
- oven
  possible status: _off, on_
- tap
  possible status: _closed, opened_
- garageDoors
  possible status: _closed, opened_

### Exampple:

### GET /device

_all devices_

### GET /device?id=0

_device with id 0_
`{
    "id": "0",
    "name": "smokeSensor",
    "status": "smokeNOTDetected"
}`

### PUT /device

_you can update any field of device except id_
`{
    "status": "smokeDetected"
}`

### GET /logs

_returns all type of logs_
_use type parameter for filtering specific logs_
Logs types:

- information
- error
- warning

### Managing server

_we are using small python server for managing main server_

Use port `8008` to manage main server

- `start` _start main server_
- `stop` _stop main server_
- `restore` _restore db_
