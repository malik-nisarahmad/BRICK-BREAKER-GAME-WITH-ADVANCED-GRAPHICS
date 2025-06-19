# 🌌 **Brick Breaker Championship** 🏓

*Smash bricks, chase scores, and vibe with cosmic flair in this dazzling arcade revival!*  

**Brick Breaker Championship** is a bold, modern reimagining of the classic brick-breaking game, crafted with **SFML** and **C++** for the **Spring 2025 OOP Hackathon**. Featuring mesmerizing particle effects, dynamic power-ups, and a swirling cursor spectacle, this game blends retro thrills with cutting-edge visuals. Ready to dominate the leaderboard? Let’s break some bricks! 💥

---

## 🎨 **Why It’s Next-Level**

- **Hypnotic Particle Effects** ✨: Ball trails, collision bursts, and a swirling cursor that dances with your mouse.
- **Vivid Themes** 🌃: Choose **Classic Charm**, **Neon Surge**, or **Stellar Void** for immersive vibes.
- **Thrilling Modes** 🎮: Play **Classic** for nostalgia, **Arcade** for chaos, or **Challenge** for intense goals.
- **Silky UI** 🖱️: Intuitive menus with scalable, responsive design.
- **Power-Up Mayhem** ⚡: Unleash **Blaze Ball**, **Multi-Ball**, and more to crush bricks.
- **Score Glory** 🏆: Track high scores and aim for legendary status.
- **Precision Physics** 🎯: Velocity-driven paddle and ball mechanics for pro-level control.

---

## 🎲 **Game Modes**

| Mode       | Experience                                          |
|------------|-----------------------------------------------------|
| **Classic**    | Pure brick-breaking with no power-ups.             |
| **Arcade**     | Wild action with power-ups and random brick types.  |
| **Challenge**  | Score-driven trials with escalating difficulty.     |

---

## 🌠 **Themes**

| Theme            | Aesthetic                                       |
|------------------|-------------------------------------------------|
| **Classic Charm** | Clean, bold colors for a retro feel.            |
| **Neon Surge**    | Glowing visuals with cyan and pink pulses.      |
| **Stellar Void**  | Starry cosmos with twinkling backgrounds.       |

---

## ⚡ **Power-Ups**

| Power-Up          | Effect                                          |
|-------------------|-------------------------------------------------|
| **Paddle Stretch** | Widen your paddle for epic ball control.        |
| **Multi-Ball**    | Split balls for a brick-busting frenzy.         |
| **Blaze Ball**    | Torch bricks with fiery red visuals.            |
| **Extra Life**    | Snag a second chance to keep smashing.          |
| **Score Blitz**   | Double points for a high-stakes rush.           |

---

## 🕹️ **Controls**

| Action                | Keys                  |
|-----------------------|-----------------------|
| Move Paddle Left      | `A` or `←`            |
| Move Paddle Right     | `D` or `→`            |
| Launch Ball           | `Space`               |
| Pause Game            | `P`                   |
| Return to Menu        | `Esc`                 |
| Restart Game          | `R` (on game over)    |

---

## 🚀 **Get Smashing!**

### Requirements
- **SFML 2.5.1+**  
- **C++17** compatible compiler  
- **CMake** (optional for builds)  

### Installation
1. **Clone the Repo**:
   ```bash
   git clone https://github.com/Team404/BrickBreakerChampionship.git
   cd BrickBreakerChampionship
   ```
2. **Build the Game**:
   ```bash
   mkdir build && cd build
   cmake .. && make
   ```
3. **Launch the Fun**:
   ```bash
   ./BrickBreakerChampionship
   ```

---

## 👨‍💻 **The Code Crafters**

- **Rana Hanan Shafique (24I-3169)**: Physics genius behind ball dynamics and collisions.  
- **Mohib Ahmad (24I-3101)**: Visual wizard crafting UI, particles, and the swirl cursor.  
- **Nisar Ahmed (24I-3131)**: Logic mastermind powering game flow and power-ups.  

---

## 🧩 **Game Architecture**

Here’s a peek at the game’s sleek, modular design, visualized with Mermaid:

```mermaid
classDiagram
    class GameManager {
        -score: int
        -lives: int
        -level: int
        -gameMode: string
        -theme: string
        +initializeLevel()
        +update()
        +handleCollisions()
        +draw()
    }
    class Ball {
        -position: Vector2f
        -velocity: Vector2f
        -radius: float
        -trail: vector<Vector2f>
        +launch()
        +update()
        +draw()
    }
    class Paddle {
        -position: Vector2f
        -size: Vector2f
        -speed: float
        +update()
        +draw()
        +getBounceAngle()
    }
    class Brick {
        -position: Vector2f
        -strength: int
        -brickType: BrickType
        +takeDamage()
        +update()
        +draw()
    }
    class PowerUp {
        -position: Vector2f
        -type: PowerUpType
        -velocity: Vector2f
        +update()
        +draw()
    }
    class Particle {
        -position: Vector2f
        -velocity: Vector2f
        -life: float
        +update()
        +draw()
    }
    class SwirlCursor {
        -particles: vector<Particle>
        -mouseTrail: deque<TrailPoint>
        +update()
        +draw()
        +setTheme()
    }
    GameManager o--> "many" Ball
    GameManager o--> Paddle
    GameManager o--> "many" Brick
    GameManager o--> "many" PowerUp
    GameManager o--> "many" Particle
    GameManager o--> SwirlCursor
    style GameManager fill:#ff4d4d,stroke:#fff,stroke-width:2px
    style Ball fill:#4dff4d,stroke:#fff,stroke-width:2px
    style Paddle fill:#4d4dff,stroke:#fff,stroke-width:2px
    style Brick fill:#ffaa4d,stroke:#fff,stroke-width:2px
    style PowerUp fill:#ff4dff,stroke:#fff,stroke-width:2px
    style Particle fill:#4dffff,stroke:#fff,stroke-width:2px
    style SwirlCursor fill:#ffff4d,stroke:#fff,stroke-width:2px
```

- **GameManager**: Orchestrates game state, collisions, and rendering.
- **Ball**: Dynamic movement with glowing trails and physics-based bounces.
- **Paddle**: Responsive controls with variable bounce angles.
- **Brick**: Diverse types with animated damage effects.
- **PowerUp**: Falling bonuses with rotating, glowing visuals.
- **Particle**: Lightweight effects for collisions and power-ups.
- **SwirlCursor**: A stunning mouse trail with swirling, colorful particles.

---

## ⚙️ **Tech Brilliance**

### Performance
- **Delta Time Scaling** ⏱️: Smooth gameplay across all frame rates.
- **Vertex Arrays** 🖼️: Optimized rendering for particle-heavy effects.
- **Object Pooling** ♻️: Efficient memory for dynamic elements.

### Design
- **OOP Mastery**: Modular classes for clean, extensible code.
- **Scalable Graphics**: Adapts to any window size with SFML.
- **Dynamic Visuals**: Theme-driven backgrounds and cursor effects.

---

## 💖 **Why You’ll Be Hooked**

**Brick Breaker Championship** is a love letter to arcade fans and code enthusiasts. With its vibrant visuals, buttery-smooth physics, and a cursor that feels alive, it’s a showcase of creativity and technical prowess. Whether you’re vibing in **Neon Surge** or battling in **Challenge** mode, this game delivers pure, unfiltered fun.

**Ready to break the mold?** Clone the repo and start smashing! 🚀  

---

*Built with 🔥 by Team404 for the Spring 2025 OOP Hackathon. Star us on GitHub! ⭐*