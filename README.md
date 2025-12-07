**Plant Watering & Pet Feeding Automation System**

An Arduino-based automation system designed to water plants and feed pets autonomously based on user-defined schedules.

**Overview**


This project automates two everyday household tasks: watering a plant and feeding a pet.

The system uses an LCD interface with physical buttons, allowing the user to configure custom intervals.

A small water pump (or servo motor for food dispensing) performs the actions automatically at the scheduled times.

**Features**


Interactive menu for setting watering and feeding intervals

Automatic plant watering based on a configurable schedule

Automated pet feeding with timing control

LCD display showing current status, menu, and confirmations


**Hardware Components**

Arduino Uno

Water pump or servo motor (for food dispenser)

16x2 LCD display

Buttons

Jumper wires, power supply, breadboard


**System Logic**

1.The user navigates the menu using physical buttons.

2.Watering and feeding intervals are selected from predefined or custom values.

3.The system stores the intervals and continuously tracks elapsed time.

4.When the configured time is reached:

        -The pump activates and waters the plant for a set duration, or
        
        -The servo rotates to release food.
        
5.The LCD displays the current status and next scheduled action
