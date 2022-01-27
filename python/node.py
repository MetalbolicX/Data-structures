from dataclasses import dataclass
from typing import TypeVar

node = TypeVar('node')

@dataclass
class Node:
    value: int = None
    next: node = None


@dataclass
class TwoWayNode(Node):
    prev: node = None