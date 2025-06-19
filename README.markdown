# Brick Breaker Championship

A modern reimagining of the classic arcade game, developed using **SFML (Simple and Fast Multimedia Library)** and **C++**. This project features advanced graphics, dynamic physics, and immersive gameplay mechanics, showcasing object-oriented programming principles with a focus on clean architecture and performance optimization.

## Key Features
- **Advanced Particle Systems**: Dynamic visual effects for ball trails, collisions, and power-ups.
- **Customizable Themes**: Choose between Classic, Neon, and Space aesthetics.
- **Multiple Game Modes**: Arcade, Classic, and Challenge modes for varied gameplay.
- **Interactive UI**: Smooth menu navigation with visual feedback.
- **Power-Up System**: Special abilities to enhance gameplay.
- **High Score Tracking**: Save and compare your best performances.
- **Responsive Controls**: Precision paddle movement with velocity-based physics.

## Game Modes
| Mode       | Description                                                  |
|------------|--------------------------------------------------------------|
| Classic    | Traditional Brick Breaker with standard bricks and no power-ups. |
| Arcade     | Enhanced experience with power-ups, multi-ball, and dynamic brick layouts. |
| Challenge  | Score-based progression with increasing difficulty and target objectives. |

## Themes
| Theme      | Visual Style                                              |
|------------|-----------------------------------------------------------|
| Classic    | Clean, minimalist design with solid colors.               |
| Neon       | Vibrant glow effects and futuristic aesthetics.           |
| Space      | Dark background with star particles and cosmic ambiance.  |

## Power-Ups
| Power-Up          | Effect                                                  |
|-------------------|---------------------------------------------------------|
| Paddle Extend     | Increases paddle size for easier ball control.          |
| Multi-Ball        | Splits the ball into multiple instances.                |
| Fire Ball         | Grants the ball destructive capabilities (visual effect only). |
| Extra Life        | Awards an additional life.                              |
| Score Multiplier  | Doubles points for a limited time.                      |

## Controls
| Action                | Key Bindings          |
|-----------------------|-----------------------|
| Move Paddle Left      | A or Left Arrow       |
| Move Paddle Right     | D or Right Arrow      |
| Launch Ball           | Space                 |
| Pause Game            | P                     |
| Return to Menu        | ESC                   |
| Restart Game          | R (when game over)    |

## Installation

### Requirements
- **SFML 2.6.1** or later
- **C++17** compatible compiler
- **CMake** (optional, for building)

### Steps
1. Clone the repository:
   ```bash
   git clone https://github.com/Team404/BrickBreakerChampionship.git
   cd BrickBreakerChampionship
   ```
2. Build the project:
   ```bash
   mkdir build && cd build
   cmake .. && make
   ```
3. Run the executable:
   ```bash
   ./BrickBreakerChampionship
   ```

## Team Members
- **Nisar Ahmad**:
- **Rana Hanan Shafique**: 
- **Mohib Ahmad**: 
 

## Technical Details

### Architecture
- **Game Manager**: Central controller for game states, scoring, and level transitions.
- **Entity Components**: Modular design for Ball, Paddle, Brick, and PowerUp classes.
- **Event Handling**: SFML-based input system with debounced key presses.

### Performance
- **Delta Time Scaling**: Ensures consistent gameplay across different frame rates.
- **Object Pooling**: Efficient memory management for particles and power-ups.
- **Vertex Arrays**: Optimized rendering for particle systems.