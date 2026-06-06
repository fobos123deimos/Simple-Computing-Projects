import pygame
from pygame.locals import RESIZABLE
from math import sqrt


class Vector2D:
    """
    Represents a two-dimensional vector.

    This class is used to store positions, targets, directions,
    and movement vectors inside the simulation world.
    """

    def __init__(self, x, y):
        self.x = float(x)
        self.y = float(y)

    def get_item(self, index):
        """
        Returns one coordinate from the vector.

        index 0 -> x
        index 1 -> y
        """
        if index == 0:
            return self.x

        if index == 1:
            return self.y

        raise IndexError("Vector2D only has indexes 0 and 1.")

    def get_vector(self):
        """
        Returns the vector as a list.
        """
        return [self.x, self.y]

    def set_item(self, index, number):
        """
        Updates one coordinate of the vector.
        """
        if index == 0:
            self.x = float(number)
        elif index == 1:
            self.y = float(number)
        else:
            raise IndexError("Vector2D only has indexes 0 and 1.")

    def set_vector(self, vector):
        """
        Updates both vector coordinates from a list, tuple, or another sequence.
        """
        self.set_item(0, vector[0])
        self.set_item(1, vector[1])

    def set_from_vector(self, vector):
        """
        Copies the coordinates from another Vector2D object.
        """
        self.set_vector(vector.get_vector())

    def get_magnitude(self):
        """
        Returns the vector magnitude.
        """
        return sqrt(self.x ** 2 + self.y ** 2)

    def normalize(self):
        """
        Normalizes the vector in place.

        If the magnitude is zero, the vector remains at (0, 0).
        """
        magnitude = self.get_magnitude()

        if magnitude == 0:
            self.set_vector([0, 0])
        else:
            self.set_vector([self.x / magnitude, self.y / magnitude])

    def get_unit_vector(self):
        """
        Returns a normalized copy of this vector.
        """
        vector = Vector2D(self.x, self.y)
        vector.normalize()
        return vector

    @staticmethod
    def get_link(vector_one, vector_two):
        """
        Returns the difference vector between two vectors.
        """
        return Vector2D(
            vector_one.get_item(0) - vector_two.get_item(0),
            vector_one.get_item(1) - vector_two.get_item(1)
        )

    def __iter__(self):
        """
        Allows unpacking:

        x, y = vector
        """
        yield self.x
        yield self.y

    def __str__(self):
        return f"({self.x:.2f}, {self.y:.2f})"

    def __add__(self, vector):
        return Vector2D(self.x + vector.x, self.y + vector.y)

    def __sub__(self, vector):
        return Vector2D(self.x - vector.x, self.y - vector.y)

    def __neg__(self):
        return Vector2D(-self.x, -self.y)

    def __mul__(self, number):
        return Vector2D(self.x * number, self.y * number)

    def __truediv__(self, number):
        return Vector2D(self.x / number, self.y / number)

    def __eq__(self, vector):
        if not isinstance(vector, Vector2D):
            return False

        return self.x == vector.x and self.y == vector.y


class State:
    """
    Base class for a finite state.

    Each state can define:
    - what happens when the entity enters the state;
    - what happens while the state is active;
    - what condition should trigger a transition;
    - what happens when the entity exits the state.
    """

    def __init__(self, name):
        self.name = name

    def get_name(self):
        return self.name

    def act(self, entity):
        """
        Executes the behavior of this state.
        """
        pass

    def check_transition(self, entity):
        """
        Checks whether this state should transition to another state.

        Return another state name to transition, or None to remain
        in the current state.
        """
        return None

    def on_enter(self, entity):
        """
        Runs when the entity enters this state.
        """
        pass

    def on_exit(self, entity):
        """
        Runs when the entity exits this state.
        """
        pass

    def __eq__(self, other):
        if not isinstance(other, State):
            return False

        return self.name == other.name


class StateMachine:
    """
    Simple finite-state machine.

    This class stores states and controls the active state of an entity.
    """

    def __init__(self):
        self.states = {}
        self.current_state = None

    def add_state(self, state):
        """
        Adds one state to the state machine.
        """
        self.states[state.get_name()] = state

        if self.current_state is None:
            self.current_state = state

    def add_states(self, states):
        """
        Adds multiple states.

        The input can be a dictionary or a list.
        """
        if isinstance(states, dict):
            for state in states.values():
                self.add_state(state)
        else:
            for state in states:
                self.add_state(state)

    def set_state(self, state_name, entity=None):
        """
        Changes the current state by name.
        """
        if state_name not in self.states:
            return

        if self.current_state is not None and entity is not None:
            self.current_state.on_exit(entity)

        self.current_state = self.states[state_name]

        if entity is not None:
            self.current_state.on_enter(entity)

    def think(self, entity=None):
        """
        Runs the current state behavior and checks for transitions.
        """
        if self.current_state is None:
            return

        self.current_state.act(entity)

        next_state_name = self.current_state.check_transition(entity)

        if next_state_name is not None:
            self.set_state(next_state_name, entity)

    def set_brain(self, new_brain):
        """
        Copies another state machine into this one.
        """
        self.states = new_brain.states
        self.current_state = new_brain.current_state


class IdleState(State):
    """
    Basic idle state used as a default placeholder.
    """

    def __init__(self):
        super().__init__("IDLE")

    def act(self, entity):
        pass


class MoveState(State):
    """
    Basic movement state used as a placeholder.
    """

    def __init__(self):
        super().__init__("MOVE")

    def act(self, entity):
        pass


class MiniWorld:
    """
    Represents a small 2D simulation world.

    The world stores entities, controls the background,
    creates the Pygame screen, updates entities, and draws them.
    """

    def __init__(self, image, area, name, entities=None):
        if entities is None:
            entities = {}

        self.entities = entities
        self.entity_id = 0
        self.image = image
        self.area = area
        self.name = name

        pygame.init()

        self.background = pygame.image.load(self.get_image()).convert()
        self.screen = pygame.display.set_mode(self.get_area(), RESIZABLE, 32)

    def add_entity(self, entity):
        """
        Adds an entity to the world and assigns a unique ID to it.
        """
        self.entities[self.entity_id] = entity
        entity.id = self.entity_id
        entity.world = self
        self.entity_id += 1

    def add_entity_list(self, entity_list):
        """
        Adds all entities from a list.
        """
        for entity in entity_list:
            self.add_entity(entity)

    def remove_entity(self, entity):
        """
        Removes an entity from the world.
        """
        if entity.id in self.entities:
            del self.entities[entity.id]

    def remove_entity_list(self, entity_list):
        """
        Removes all entities from a list.
        """
        for entity in entity_list:
            self.remove_entity(entity)

    def get(self, entity_id):
        """
        Returns an entity by ID.
        """
        return self.entities.get(entity_id)

    def get_name(self):
        return self.name

    def get_entities(self):
        return self.entities

    def get_entity_list(self, first_id, last_id):
        """
        Returns a list of entities inside the selected ID range.
        """
        entity_list = []

        for entity_id in range(first_id, last_id):
            entity = self.get(entity_id)

            if entity is not None:
                entity_list.append(entity)

        return entity_list

    def get_current_entity_id(self):
        return self.entity_id

    def get_image(self):
        return self.image

    def get_area(self):
        return self.area

    def get_background(self):
        return self.background

    def get_screen(self):
        return self.screen

    def set_name(self, new_name):
        self.name = new_name

    def set_background(self, image, area):
        """
        Updates the world background and/or screen area.
        """
        if image != self.get_image() and image != 0:
            self.image = image
            self.background = pygame.image.load(image).convert()

        if area != self.get_area() and area != 0:
            self.area = area
            self.screen = pygame.display.set_mode(area, RESIZABLE, 32)

    def set_entity(self, entity_id, new_entity):
        self.entities[entity_id] = new_entity

    def set_entities(self, new_entities):
        self.entities = new_entities

    def set_current_entity_id(self, new_id):
        self.entity_id = new_id

    def set_world(self, new_world):
        """
        Copies selected information from another MiniWorld object.
        """
        if new_world.get_entities() != 0:
            self.set_entities(new_world.get_entities())

        if new_world.get_current_entity_id() != 0:
            self.set_current_entity_id(new_world.get_current_entity_id())

        if new_world.get_background() != 0 or new_world.get_image() != 0:
            self.set_background(new_world.get_image(), new_world.get_area())

        if new_world.get_name() != 0:
            self.set_name(new_world.get_name())

    def process(self, elapsed_time):
        """
        Updates all entities in the world.
        """
        for entity in list(self.get_entities().values()):
            entity.process(elapsed_time)

    def draw_background(self):
        """
        Draws the background and every entity on the screen.
        """
        self.screen.blit(self.get_background(), (0, 0))

        for entity in list(self.get_entities().values()):
            entity.draw(self.get_screen())

    def __str__(self):
        entity_text = ""

        for entity in list(self.get_entities().values()):
            entity_text += str(entity) + "\n"

        return (
            f"{' ' * 35}{self.get_name()}{' ' * 35}\n"
            f"{'-' * 80}\n"
            f"Quantity: {len(self.get_entities())} "
            f"Current ID: {self.get_current_entity_id()} "
            f"Area: {self.get_area()} "
            f"Image: {self.get_image()}\n\n"
            f"{entity_text}"
        )

    def __eq__(self, other):
        if not isinstance(other, MiniWorld):
            return False

        return (
            self.get_entities() == other.get_entities()
            and self.get_current_entity_id() == other.get_current_entity_id()
            and self.get_image() == other.get_image()
            and self.get_area() == other.get_area()
            and self.get_background() == other.get_background()
            and self.get_screen() == other.get_screen()
        )


class Entity:
    """
    Represents an entity inside the simulation world.

    An entity has:
    - a world;
    - a name;
    - an image;
    - a position;
    - a target;
    - a speed;
    - a vision radius;
    - a state machine.
    """

    def __init__(
        self,
        world,
        name,
        image,
        position=None,
        target=None,
        speed=0.0,
        vision_radius=0.0,
        entity_id=0
    ):
        if position is None:
            position = Vector2D(0.0, 0.0)

        if target is None:
            target = Vector2D(0.0, 0.0)

        self.world = world
        self.name = name
        self.image = image
        self.sprite = pygame.image.load(self.get_image()).convert_alpha()
        self.position = position
        self.target = target
        self.speed = float(speed)
        self.vision_radius = float(vision_radius)
        self.brain = StateMachine()
        self.id = entity_id

    def get_world(self):
        return self.world

    def get_name(self):
        return self.name

    def get_image(self):
        return self.image

    def get_position(self):
        return self.position

    def get_target(self):
        return self.target

    def get_speed(self):
        return self.speed

    def get_id(self):
        return self.id

    def get_sprite(self):
        return self.sprite

    def get_brain(self):
        return self.brain

    def get_vision_radius(self):
        return self.vision_radius

    def set_world(self, world):
        self.world = world

    def set_name(self, name):
        self.name = name

    def set_image(self, image):
        self.image = image
        self.sprite = pygame.image.load(image).convert_alpha()

    def set_position(self, position):
        self.position = position

    def set_target(self, target):
        self.target = target

    def set_speed(self, speed):
        self.speed = float(speed)

    def set_id(self, new_id):
        self.id = new_id

    def set_sprite(self, image):
        self.sprite = pygame.image.load(image).convert_alpha()

    def set_vision_radius(self, new_vision_radius):
        self.vision_radius = float(new_vision_radius)

    def set_brain(self, new_brain):
        self.brain.set_brain(new_brain)

    def set_entity(self, other):
        """
        Copies selected information from another entity.
        """
        if other.get_world() != 0:
            self.set_world(other.get_world())

        if other.get_name() != 0:
            self.set_name(other.get_name())

        if other.get_image() != 0:
            self.set_image(other.get_image())

        if other.get_position() != 0:
            self.set_position(other.get_position())

        if other.get_target() != 0:
            self.set_target(other.get_target())

        if other.get_speed() != 0:
            self.set_speed(other.get_speed())

        if other.get_brain() != 0:
            self.set_brain(other.get_brain())

        if other.get_id() != 0:
            self.set_id(other.get_id())

        if other.get_vision_radius() != -1:
            self.set_vision_radius(other.get_vision_radius())

    def draw(self, surface):
        """
        Draws the entity centered at its current position.
        """
        x, y = self.get_position()
        width, height = self.get_sprite().get_size()
        surface.blit(self.get_sprite(), (x - width / 2, y - height / 2))

    def process(self, elapsed_time):
        """
        Updates the entity.

        The entity runs its state machine and moves toward its target
        if it has a positive speed.
        """
        self.get_brain().think(self)

        if self.get_speed() > 0 and self.get_position() != self.get_target():
            destination_vector = self.get_target() - self.get_position()
            target_distance = destination_vector.get_magnitude()
            direction_vector = destination_vector.get_unit_vector()
            movement_distance = min(target_distance, elapsed_time * self.get_speed())

            self.set_position(self.get_position() + direction_vector * movement_distance)

    def get_world_vision(self, name):
        """
        Searches for a visible entity by name inside the same world.
        """
        if self.world is None:
            return None

        position = self.get_position()

        for entity in list(self.world.get_entities().values()):
            if entity.get_name() == name:
                distance = Vector2D.get_link(position, entity.get_position()).get_magnitude()

                if distance < self.get_vision_radius():
                    return entity

        return None

    def __str__(self):
        return (
            f"Name: {self.get_name()} "
            f"Image: {self.get_image()} "
            f"Position: {self.get_position()} "
            f"Target: {self.get_target()} "
            f"Speed: {self.get_speed()} "
            f"Vision radius: {self.get_vision_radius()} "
            f"ID: {self.get_id()} "
            f"Brain: {self.get_brain()}"
        )

    def __eq__(self, other):
        if not isinstance(other, Entity):
            return False

        return (
            self.get_world() == other.get_world()
            and self.get_name() == other.get_name()
            and self.get_sprite() == other.get_sprite()
            and self.get_position() == other.get_position()
            and self.get_target() == other.get_target()
            and self.get_speed() == other.get_speed()
            and self.get_id() == other.get_id()
            and self.get_vision_radius() == other.get_vision_radius()
            and self.get_brain() == other.get_brain()
        )


class Central(Entity):
    """
    Represents a central control entity.

    The central entity can store robots, core states, and a control radius.
    """

    def __init__(self, world, image, radius=50.0):
        super().__init__(world, "Central", image)

        self.robots = {}
        self.core_states = {
            "IDLE": IdleState(),
            "MOVE": MoveState()
        }

        self.brain.add_states(self.get_core_states())
        self.control_radius = float(radius)

    def get_brain(self):
        return self.brain

    def get_robots(self):
        return self.robots

    def get_control_radius(self):
        return self.control_radius

    def get_core_states(self):
        return self.core_states

    def set_robots(self, new_robots):
        self.robots = new_robots

    def set_core_states(self, core_states):
        self.core_states = core_states
        self.brain.add_states(self.get_core_states())

    def set_control_radius(self, control_radius):
        self.control_radius = float(control_radius)

    def add_core_state(self, state):
        self.core_states[state.get_name()] = state
        self.brain.add_states(self.get_core_states())

    def remove_core_state(self, state_name):
        if state_name in self.core_states:
            del self.core_states[state_name]
            self.brain.add_states(self.get_core_states())

    def set_entity(self, other):
        """
        Copies selected information from another central entity.
        """
        super().set_entity(other)

        if other.get_robots() != 0:
            self.set_robots(other.get_robots())

        if other.get_core_states() != 0:
            self.set_core_states(other.get_core_states())

        if other.get_control_radius() != 0:
            self.set_control_radius(other.get_control_radius())

    def __str__(self):
        return (
            super().__str__()
            + f" Robots: {self.get_robots()}"
            + f" Core states: {list(self.get_core_states().keys())}"
            + f" Control radius: {self.get_control_radius()}"
        )

    def __eq__(self, other):
        if not isinstance(other, Central):
            return False

        return (
            super().__eq__(other)
            and self.get_robots() == other.get_robots()
            and self.get_core_states() == other.get_core_states()
            and self.get_control_radius() == other.get_control_radius()
        )

    def draw(self, surface):
        """
        Draws the central entity and its control radius.
        """
        super().draw(surface)
        pygame.draw.circle(
            surface,
            (200, 255, 200),
            tuple(self.get_position().get_vector()),
            int(self.get_control_radius()),
            1
        )


# Future development idea:
# Implement a planar travel system where an entity can move from one world
# to another. This will require a WorldManager class that stores worlds
# indexed by ID. To move between worlds, an entity may only need to change
# its current world ID. This may also allow entities to influence other worlds
# remotely.
#
# Suggested future classes and changes:
# - PlanarTravel
# - WorldManager
# - world_id attribute inside MiniWorld
# - travel_to_world method inside Entity
# - interface for remote influence between worlds