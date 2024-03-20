# package-collection-and-delivery

This project integrates Arduino Uno, HC-05 Bluetooth module, and ESP32 microcontroller to create an intelligent package collection and delivery system. With user-friendly interface and robust hardware communication, this system enables users to select desired products from a predetermined list, after which a cart autonomously navigates to collect the selected items for delivery.

Features:

    User-Friendly Interface: Utilize a simple interface for users to select desired products from a predefined list provided by the shop.
    Autonomous Cart Navigation: Employ ESP32 to control the cart's movement, enabling it to navigate to the specified product locations.
    Bluetooth Communication: Establish communication between the user interface (via HC-05 Bluetooth module and esp32) and the cart for seamless interaction.esp32 is the master and hc 05 is the slave.
    Product Verification: Ensure the cart collects only the products selected by the user, enhancing accuracy and reliability using few ir sensors.
    Real-Time Status Updates: Provide users with real-time updates on the status of their package collection and delivery process.

Technologies Used:

    Arduino Uno: Control system for the cart's movement .
    ESP32 Microcontroller: Powers the autonomous navigation and decision-making capabilities of the cart and take the orders from user what he/she wants and how many.
    HC-05 Bluetooth Module: Facilitates wireless communication between the esp32 and the cart.
    User Interface: Develop a simple web interface for users to interact with the system and select desired products.
