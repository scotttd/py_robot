#!/usr/bin/python
# sendandreceivearguments.py
# Author: Adrien Emery
# Make sure the you have the SendAndReceiveArguments example loaded onto the Arduino
import random
import sys
import serial
import time
import RPi.GPIO as GPIO

from cmdmessenger import CmdMessenger
from serial.tools import list_ports

# Variables for GPIO switches
GPIO.setmode(GPIO.BOARD)
GPIO.setup(11, GPIO.IN, pull_up_down=GPIO.PUD_UP)
GPIO.setup(12, GPIO.IN, pull_up_down=GPIO.PUD_UP)
n = 1

class SendAndReceiveArguments(object):

    def __init__(self):
        # make sure this baudrate matches the baudrate on the Arduino
        self.running = False
        self.baud = 57600
        self.commands = ['acknowledge',
                         'error',
                         'drive_robot',
                         'robot_status',
                         ]

        try:
            # try to open the first available usb port
            self.port_name = self.list_usb_ports()[0][0]
			# Initialize an ArduinoBoard instance.  This is where you specify baud rate and
            # serial timeout.  If you are using a non ATmega328 board, you might also need
            # to set the data sizes (bytes for integers, longs, floats, and doubles).  
            #arduino = PyCmdMessenger.ArduinoBoard("/dev/ttyACM0",baud_rate=9600)
            self.serial_port = serial.Serial(self.port_name, self.baud, timeout=0)
        except (serial.SerialException, IndexError):
            raise SystemExit('Could not open serial port.')
        else:
            print('Serial port sucessfully opened.')
	    # Initialize the messenger
            self.messenger = CmdMessenger(self.serial_port)

	    # attach callbacks
            self.messenger.attach(func=self.on_error, msgid=self.commands.index('error'))
            self.messenger.attach(func=self.on_robot_status, msgid=self.commands.index('robot_status'))
            
	    # send a command that the arduino will acknowledge
            self.messenger.send_cmd(self.commands.index('acknowledge'))
            # Wait until the arduino sends and acknowledgement back
            self.messenger.wait_for_ack(ackid=self.commands.index('acknowledge'))
            print('Arduino Ready')

    def list_usb_ports(self):
        """ Use the grep generator to get a list of all USB ports.
        """
        ports =  [port for port in list_ports.grep('USB')]
        return ports

    def on_error(self, received_command, *args, **kwargs):
        """Callback function to handle errors
        """
        print('Error:', args[0][0])

    def on_robot_status(self, received_command, *args, **kwargs):
        """Callback to handle the float addition response
        """
        print('Robot Status:', args[0][0])

    def stop(self):
        self.running = False

    def run(self):
        """Main loop to send and receive data from the Arduino
        """
        self.running = True
        timeout = 2
        pin_timeout = 2
        t0 = time.time()
        t0_pin = time.time()
        while self.running:
            if (GPIO.input(11)== False) and (time.time()-t0_pin > pin_timeout):
              time.sleep(0.2)#Delay for debounce
              t0_pin = time.time()
              # Send
              print("pin 11")
              drive_time = 1000
              self.messenger.send_cmd(self.commands.index('drive_robot'), drive_time)
              print("Sent drive command")
              time.sleep(1)
              #c.send("go_straight")
              #time.sleep (1)#Delay for go command
            if GPIO.input(12)== False:
              time.sleep(0.2)#Delay for debounce
              print("pin 12")
              n=2


            # Check to see if any data has been received
            self.messenger.feed_in_data()


if __name__ == '__main__':
    send_and_receive_args = SendAndReceiveArguments()

    try:
        print('Press Ctrl+C to exit...')
        print()
        send_and_receive_args.run()
    except KeyboardInterrupt:
        send_and_receive_args.stop()
        print('Exiting...')
