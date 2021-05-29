import numpy as np


class Token:
    ip_source: str = ""
    ip_destination: str = ""
    message: str = ""
    arrived_at_destination: bool = False
    free: bool = True
    history: list = []

    def __init__(self, ip_source, ip_destination, message, arrived_at_destination, free, history):
        self.ip_source = ip_source
        self.ip_destination = ip_destination
        self.message = message
        self.arrived_at_destination = arrived_at_destination
        self.free = free
        self.history = [history]

    def print_token(self):
        print(f"Token:\n ip_source:{self.ip_source}\n ip_destination:{self.ip_destination}\n "
              f"message:{self.message}\n arrived_at_destination:{self.arrived_at_destination}\n "
              f"free:{self.free}\n history:{self.history}\n ")

    def clear_token(self):
        self.ip_source: str = ""
        self.ip_destination: str = ""
        self.message: str = ""
        self.arrived_at_destination: bool = False
        self.free: bool = True
        self.history = []


def token_ring_clockwise(number_of_computers: int, ip_source: int, ip_destination: int, message: str):
    assert 0 < ip_source <= number_of_computers
    assert 0 < ip_destination <= number_of_computers
    r = np.random.randint(0, 255, 3)
    list_of_computers: list = []
    for index in range(number_of_computers):
        list_of_computers.append(str(r[0]) + '.' + str(r[1]) + '.' + str(r[2]) + '.' + str(index + 1))
    token = Token(list_of_computers[ip_source - 1], list_of_computers[ip_destination - 1], message, False, False,
                  list_of_computers[ip_source - 1])
    current_computer = ip_source + 1
    if current_computer == len(list_of_computers) + 1:
        current_computer = 1
    if token.ip_source == token.ip_destination:
        print(f"Message transmitted:{message}")
        token.arrived_at_destination = True
    token.print_token()

    while list_of_computers[current_computer - 1] != token.ip_source or not token.arrived_at_destination:
        if list_of_computers[current_computer - 1] == token.ip_destination:
            print(f"Message transmitted:{message}")
            token.arrived_at_destination = True
            token.history.append(list_of_computers[current_computer - 1])
        else:
            token.history.append(list_of_computers[current_computer - 1])
        if current_computer == len(list_of_computers):
            current_computer = 1
        else:
            current_computer += 1
        token.print_token()

    token.history.append(list_of_computers[current_computer - 1])
    token.print_token()

    token.clear_token()
    token.print_token()

    user_input: str = input("Would you like to continue the network?(Yes/No or Y/N or y/n):")
    if user_input == "Yes" or user_input == "Y" or user_input == "y":
        new_user_ip_source = input("Please insert the new ip source:")
        new_user_ip_destination = input("Please insert the new ip destination:")
        new_user_ip_message = input("Please insert the new message:")
        new_user_way = input("Please insert the new way of the network clockwise(1) or anticlockwise(2):")

        while int(new_user_way) != 1 and int(new_user_way) != 2:
            new_user_way = input("Please insert the way of the network clockwise(1) or anticlockwise(2):")
        if int(new_user_way) == 1:
            token_ring_clockwise(number_of_computers, int(new_user_ip_source), int(new_user_ip_destination),
                                 new_user_ip_message)
        else:
            token_ring_anticlockwise(number_of_computers, int(new_user_ip_source), int(new_user_ip_destination),
                                     new_user_ip_message)


def token_ring_anticlockwise(number_of_computers: int, ip_source: int, ip_destination: int, message: str):
    assert 0 < ip_source <= number_of_computers
    assert 0 < ip_destination <= number_of_computers

    r = np.random.randint(0, 255, 3)
    list_of_computers: list = []
    for index in range(number_of_computers):
        list_of_computers.append(str(r[0]) + '.' + str(r[1]) + '.' + str(r[2]) + '.' + str(index + 1))
    token = Token(list_of_computers[ip_source - 1], list_of_computers[ip_destination - 1], message, False, False,
                  list_of_computers[ip_source - 1])
    current_computer = ip_source - 1
    if current_computer == 0:
        current_computer = len(list_of_computers)
    if token.ip_source == token.ip_destination:
        print(f"Message transmitted:{message}")
        token.arrived_at_destination = True
    token.print_token()

    while list_of_computers[current_computer - 1] != token.ip_source or not token.arrived_at_destination:
        if list_of_computers[current_computer - 1] == token.ip_destination:
            print(f"Message transmitted:{message}")
            token.arrived_at_destination = True
            token.history.append(list_of_computers[current_computer - 1])
        else:
            token.history.append(list_of_computers[current_computer - 1])
        if current_computer == 1:
            current_computer = len(list_of_computers)
        else:
            current_computer -= 1
        token.print_token()

    token.history.append(list_of_computers[current_computer - 1])
    token.print_token()

    token.clear_token()
    token.print_token()

    user_input: str = input("Would you like to continue the network?(Yes/No or Y/N or y/n):")
    if user_input == "Yes" or user_input == "Y" or user_input == "y":
        new_user_ip_source = input("Please insert the new ip source:")
        new_user_ip_destination = input("Please insert the new ip destination:")
        new_user_ip_message = input("Please insert the new message:")
        new_user_way = input("Please insert the new way of the network clockwise(1) or anticlockwise(2):")

        while int(new_user_way) != 1 and int(new_user_way) != 2:
            new_user_way = input("Please insert the way of the network clockwise(1) or anticlockwise(2):")
        if int(new_user_way) == 1:
            token_ring_clockwise(number_of_computers, int(new_user_ip_source), int(new_user_ip_destination),
                                 new_user_ip_message)
        else:
            token_ring_anticlockwise(number_of_computers, int(new_user_ip_source), int(new_user_ip_destination),
                                     new_user_ip_message)


user_number_of_computers = input("Please insert the number of computer in the network:")
user_ip_source = input("Please insert the ip source:")
user_ip_destination = input("Please insert the ip destination:")
user_ip_message = input("Please insert the message:")
user_way = input("Please insert the way of the network clockwise(1) or anticlockwise(2):")

while int(user_way) != 1 and int(user_way) != 2:
    user_way = input("Please insert the way of the network clockwise(1) or anticlockwise(2):")
if int(user_way) == 1:
    token_ring_clockwise(int(user_number_of_computers), int(user_ip_source), int(user_ip_destination), user_ip_message)
else:
    token_ring_anticlockwise(int(user_number_of_computers), int(user_ip_source), int(user_ip_destination),
                             user_ip_message)
