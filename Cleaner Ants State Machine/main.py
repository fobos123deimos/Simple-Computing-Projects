import random
from pathlib import Path

import pygame

from simulation import Vector2D, Entity, State


WINDOW_WIDTH = 1000
WINDOW_HEIGHT = 700
FPS = 60

ANT_COUNT = 20
ANT_SPEED = 130
CAPTURE_DISTANCE = 28
BASE_RADIUS = 55

ASSETS_DIR = Path(__file__).parent

ANT_IMAGE = ASSETS_DIR / "ant.png"
LEAF_IMAGE = ASSETS_DIR / "leaf.png"


class SearchState(State):
    """
    State where the ant searches for its assigned leaf.
    """

    def __init__(self):
        super().__init__("SEARCH")

    def on_enter(self, entity):
        entity.carrying_leaf = False

    def act(self, entity):
        entity.set_target(entity.leaf_position)
        entity.set_speed(ANT_SPEED)

    def check_transition(self, entity):
        distance = (entity.get_position() - entity.leaf_position).get_magnitude()

        if distance <= CAPTURE_DISTANCE:
            return "BRING"

        return None


class BringState(State):
    """
    State where the ant brings the leaf back to the central base.
    """

    def __init__(self):
        super().__init__("BRING")

    def on_enter(self, entity):
        entity.carrying_leaf = True

    def act(self, entity):
        entity.set_target(entity.base_position)
        entity.set_speed(ANT_SPEED)

    def check_transition(self, entity):
        distance = (entity.get_position() - entity.base_position).get_magnitude()

        if distance <= BASE_RADIUS:
            entity.carrying_leaf = False
            entity.assign_new_leaf()
            return "SEARCH"

        return None


class CleanerAnt(Entity):
    """
    Ant entity controlled by a finite state machine.

    Each ant has:
    - a central base;
    - one current leaf target;
    - a carrying state;
    - its own state machine.
    """

    def __init__(self, image, base_position, start_position, ant_id):
        super().__init__(
            world=None,
            name=f"Ant {ant_id}",
            image=str(image),
            position=start_position,
            target=base_position,
            speed=ANT_SPEED,
            vision_radius=250,
            entity_id=ant_id
        )

        self.base_position = base_position
        self.carrying_leaf = False
        self.leaf_position = self.create_random_leaf_position()

        self.get_brain().add_state(SearchState())
        self.get_brain().add_state(BringState())
        self.get_brain().set_state("SEARCH", self)

    def create_random_leaf_position(self):
        """
        Creates a random leaf position away from the central base.
        """
        while True:
            x = random.randint(60, WINDOW_WIDTH - 60)
            y = random.randint(60, WINDOW_HEIGHT - 60)

            leaf_position = Vector2D(x, y)
            distance_from_base = (leaf_position - self.base_position).get_magnitude()

            if distance_from_base > 180:
                return leaf_position

    def assign_new_leaf(self):
        """
        Assigns a new leaf after the ant reaches the base.
        """
        self.leaf_position = self.create_random_leaf_position()


def create_start_position(base_position, index, total_ants):
    """
    Places ants around the central base instead of stacking all of them
    at exactly the same point.
    """
    angle = (2 * 3.14159 * index) / total_ants
    radius = 75

    x = base_position.x + radius * pygame.math.Vector2(1, 0).rotate_rad(angle).x
    y = base_position.y + radius * pygame.math.Vector2(1, 0).rotate_rad(angle).y

    return Vector2D(x, y)


def draw_text(screen, text, position, font, color=(255, 255, 255)):
    """
    Draws text on the screen.
    """
    rendered_text = font.render(text, True, color)
    screen.blit(rendered_text, position)


def draw_base(screen, base_position, font):
    """
    Draws the central base.
    """
    pygame.draw.circle(
        screen,
        (80, 130, 255),
        tuple(base_position.get_vector()),
        BASE_RADIUS,
        3
    )

    pygame.draw.circle(
        screen,
        (80, 130, 255),
        tuple(base_position.get_vector()),
        8
    )

    draw_text(
        screen,
        "CENTRAL BASE",
        (base_position.x - 70, base_position.y + BASE_RADIUS + 10),
        font
    )


def main():
    pygame.init()

    screen = pygame.display.set_mode((WINDOW_WIDTH, WINDOW_HEIGHT))
    pygame.display.set_caption("State Machine - 20 Cleaner Ants")

    clock = pygame.time.Clock()
    font = pygame.font.SysFont("arial", 22)

    base_position = Vector2D(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2)

    leaf_sprite = pygame.image.load(str(LEAF_IMAGE)).convert_alpha()
    leaf_sprite = pygame.transform.smoothscale(leaf_sprite, (30, 30))

    ants = []

    for index in range(ANT_COUNT):
        start_position = create_start_position(base_position, index, ANT_COUNT)

        ant = CleanerAnt(
            image=ANT_IMAGE,
            base_position=base_position,
            start_position=start_position,
            ant_id=index + 1
        )

        ant.sprite = pygame.transform.smoothscale(ant.sprite, (32, 32))

        ants.append(ant)

    running = True

    while running:
        elapsed_time = clock.tick(FPS) / 1000.0

        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                running = False

        for ant in ants:
            ant.process(elapsed_time)

        screen.fill((28, 32, 38))

        draw_base(screen, base_position, font)

        for ant in ants:
            if ant.carrying_leaf:
                leaf_position = ant.get_position()
            else:
                leaf_position = ant.leaf_position

            leaf_width, leaf_height = leaf_sprite.get_size()

            screen.blit(
                leaf_sprite,
                (
                    leaf_position.x - leaf_width / 2,
                    leaf_position.y - leaf_height / 2
                )
            )

        for ant in ants:
            ant.draw(screen)

        searching_count = 0
        bringing_count = 0

        for ant in ants:
            current_state = ant.get_brain().current_state.get_name()

            if current_state == "SEARCH":
                searching_count += 1
            elif current_state == "BRING":
                bringing_count += 1

        draw_text(screen, "State Machine Simulation", (20, 20), font)
        draw_text(screen, f"Ants: {ANT_COUNT}", (20, 50), font)
        draw_text(screen, f"Searching: {searching_count}", (20, 80), font)
        draw_text(screen, f"Bringing: {bringing_count}", (20, 110), font)
        draw_text(screen, "Close the window to exit.", (20, 140), font)

        pygame.display.flip()

    pygame.quit()


if __name__ == "__main__":
    main()