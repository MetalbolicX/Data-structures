from sys import maxsize
from dataclasses import dataclass
from node import TwoWayNode
from typing import Generator


@dataclass
class CircularDoublyLinkedList:
    pass


    def __post_init__(self):
        self.__head: TwoWayNode = None
        self.__tail: TwoWayNode = None
        self.__count: int = 0


    @property
    def head(self) -> TwoWayNode:
        """Gets the property of the head of the circular doubly linked list."""
        return self.__head


    @property
    def tail(self) -> TwoWayNode:
        """Gets the property of the tail of the circular doubly linked list."""
        return self.__tail


    @property
    def count(self) -> int:
        """Returns the number of items in the circular doubly linked list."""
        return self.__count


    def __len__(self) -> int:
        """Returns the count of nodes in the circular doubly linked list."""
        return self.__count


    def __str__(self) -> str:
        """Returns the string representation of the circular doubly linked list."""
        return f'CircularDoublyLinkedList(head={self.head}, tail={self.tail}, count={self.__count})'


    def __existance_of_elements(self):
        """Asserts if there is any node in the list."""
        ## Evaluate the existence of the single linked list
        assert self.head, 'There are no elements in the doubly linked list. Use the add or append method.'


    def __iter__(self, reverse: bool) -> Generator:
        """Iterates through the all nodes of the circular doubly linked list."""
        ## If there is not head
        self.__existance_of_elements()

        ## Iterate until the last element of the list
        probe: TwoWayNode = self.head if not reverse else self.tail

        for _ in range(self.count):
            yield probe
            probe = probe.next if not reverse else probe.prev


    def display(self, reverse: bool = False):
        """Display all nodes values of the circular doubly linked list."""
        self.__existance_of_elements()

        for node in self.__iter__(reverse):
            print(node.value)


    def __verify_index(self, index: int):
        """Verifies the index of the input."""
        if not(-1 <= index < self.count):
            raise IndexError(f'The index value: {index} is out of range in the circular doubly linked list.')


    def push(self, value: int):
        """Adds a node to the begging of the circular doubly linked list."""
        
        new_node: TwoWayNode = TwoWayNode(value)
        
        if not self.head:
            self.__head = self.__tail = new_node
            self.__head.prev = self.tail
            self.__head.next = self.head
        else:
            self.__head.prev = new_node
            new_node.next = self.head
            new_node.prev = self.tail
            self.__head = new_node

        self.__count += 1
        

    def append(self, value: int):
        """Appends node to the end of the circular doubly linked list."""

        new_node: TwoWayNode = TwoWayNode(value)

        if not self.head:
            self.__head = self.__tail = new_node
            self.__head.prev = self.tail
            self.__head.next = self.head
        else:
            self.__tail.next = new_node
            new_node.prev = self.tail
            new_node.next = self.head
            self.__tail = new_node

        self.__count += 1


    def insert(self, index: int, value: int):
        """Inserts a new node in function of the index."""
        self.__existance_of_elements()
        ## Verify if list is empty
        self.__verify_index(index)

        ## Inserts on the index
        if index == 0:
            ## Add the beginning
            self.push(value)
        elif index in [-1, self.count-1]:
            ## Add the end of the single linked list
            self.append(value)
        else:
            probe: TwoWayNode = self.head

            for _ in range(index-1):
                probe = probe.next

            probe.next = TwoWayNode(value, probe.next, probe)
            probe.next.next.prev = probe.next
            self.__count += 1


    def insert_sorted(self, value: int):
        """Insert a new node into the sorted list."""
        self.__existance_of_elements()

        if self.head.value >= value:
            self.push(value)
        elif self.tail.value <= value:
            self.append(value)
        else:
            probe: TwoWayNode = self.head.next

            while probe != self.tail and probe.value <= value and not(probe.value > value):
                probe = probe.next

            probe.prev.next = TwoWayNode(value, probe, probe.prev)
            probe.prev = probe.prev.next
            self.__count += 1


    def before_value(self, existing_value: int, value: int):
        """Inserts a new node before the first appearance of a given value."""
        ## Evaluate if the single linked list is empty
        self.__existance_of_elements()

        ## Evaluate the insertion
        if self.head.value == existing_value:
            self.push(value)
        else:
            probe: TwoWayNode = self.head

            while probe != self.tail and probe.value != existing_value:
                probe = probe.next

            if probe.value == existing_value:
                probe.prev.next = TwoWayNode(value, probe, probe.prev)
                probe.prev = probe.prev.next
                self.__count += 1


    def after_value(self, existing_value: int, value: int):
        """Inserts a new node after the first appearance of given value."""
        ## Evaluate the existance
        self.__existance_of_elements()

        if self.count == 1 and self.head.value == existing_value:
            self.append(value)
        else:
            probe: TwoWayNode = self.head

            while probe != self.tail and probe.value != existing_value:
                probe = probe.next

            if probe == self.tail and probe.value == existing_value:
                self.append(value)
            elif probe.value == existing_value:
                probe.next = TwoWayNode(value, probe.next, probe)
                probe.next.next.prev = probe.next
                self.__count += 1


    def index(self, value: int) -> list[int]:
        """Search for the index of the given value and return the list of indixes"""
        return [
            i for i, node in enumerate(self.__iter__()) if node.value == value
        ]


    def clear(self):
        """Deletes the single linked list."""
        self.__head = None
        self.__tail = None
        self.__count = 0


    def pop(self):
        """Deletes the last node of the circular doubly linked list."""
        ## Evaluates if the list is empty
        self.__existance_of_elements()

        ## If there is only one element
        if self.count == 1:
            self.clear()
        else:
            ## Reassign the tail
            self.__tail = self.tail.prev
            self.__tail.next = self.__head
            self.__count -= 1


    def shift(self):
        """Deletes the first node of the circular doubly linked list."""
        ## Evaluates if the list is empty
        self.__existance_of_elements()

        ## If there is only one element
        if self.__count == 1:
            self.clear()
        else:
            self.__head = self.__head.next
            self.__head.prev = self.tail
            self.__tail.next = self.head
            self.__count -= 1


    def delete(self, index: int):
        """Deletes and element by an index."""
        ## Verify the index
        self.__verify_index(index)
        
        ## If there is only one element in the list
        if self.count == 1:
            self.clear()
            return

        if index == 0:
            self.shift()
        elif index in [-1, self.count-1]:
            self.pop()
        else:
            probe: TwoWayNode = self.head
            
            for _ in range(index):
                probe = probe.next

            probe.prev.next = probe.next
            probe.next.prev = probe.prev
            self.__count -= 1


    def remove(self, value: int):
        """Deletes the first appearance of the given value."""
        ## Evaluates if the list is empty
        self.__existance_of_elements()

        if self.head.value == value:
            self.shift()
            return

        probe: TwoWayNode = self.head

        while probe != self.tail and probe.value != value:
            probe = probe.next

        if probe == self.tail and probe.value == value:
            self.pop()
        elif probe != self.tail and probe.value == value:
            probe.prev.next = probe.next
            probe.next.prev = probe.prev
            self.__count -= 1


    def remove_duplicates_sorted(self):
        """Remove the duplicates values in the list."""
        self.__existance_of_elements()

        probe: TwoWayNode = self.head.next
        temp: TwoWayNode = None

        while probe != self.tail:

            if probe.prev.value != probe.value:
                probe = probe.next
            else:
                temp = probe.next
                probe.prev.next = temp
                temp.prev = probe.prev
                self.__count -= 1
                probe = temp

        if probe == self.tail and probe.prev.value == probe.value:
            self.pop()


    def check_sort(self) -> bool:
        """Check if the list is sorted."""
        self.__existance_of_elements()

        x: int -maxsize - 1

        for node in self.__iter__():
            if node.value < x:
                return False

            x = node.value

        return True


    def replace(self, old_value: int,value: int, entire: bool = False):
        """Replaces the first occurrence of the given value with new one or all apperances. By default replace the first appearance."""
        ## Evaluates if the list is empty
        self.__existance_of_elements()
        
        ## Iterate through all the elements in case the all entire parameter is true
        for node in self.__iter__():
            if node.value == old_value:
                node.value = value
                if not entire:
                    break


    def update(self, index: int, value: int):
        """Updates a value in the list by a given index."""
        self.__existance_of_elements()
        ## Evaluates the correct index
        self.__verify_index(index)

        ## Iterate until the given index is reached
        probe: TwoWayNode = self.head
        for _ in range(index):
            probe = probe.next
        
        ## Updates the value
        probe.value = value


    def reverse(self):
        """Reverse the circular doubly linked list backwards."""
        ## Evaluates if the list is empty
        self.__existance_of_elements()

        probe: TwoWayNode = self.head
        prev_node: TwoWayNode = None
        next_node: TwoWayNode = None

        self.__tail = probe

        for _ in range(self.count):
            next_node = probe.next
            probe.next = prev_node
            probe.prev = next_node
            prev_node = probe
            probe = next_node

        self.__head = prev_node
        self.__head.prev = self.tail
        self.__tail.next = self.head