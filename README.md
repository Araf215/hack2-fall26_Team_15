# Hackathon #2 | Team 15

**CSC 10300 – Fall 2026 | CCNY**

## Team Members
- Aoanul Hoque
- Jeremy Ramales
- Edgar Ganahl

## Project Overview
This project is being developed for hackathon #2 and is inspired by Kate Crawford and Vladan Joler's [Calculating Empires](https://calculatingempires.net/).

Our goal is to create an original, interactive c++ application exploring the relationship between technology, society, and the concepts of abstraction, efficiency, or recursion.

**Project Title:**
FlockWatch

**Project Description:**

FlockWatch is an interactive simulation of flock camera surveillance around the CCNY campus and its surrounding streets. Using a satellite map, the program simulates vehicles traveling through areas monitored by fictional Flock cameras. When vehicles enter a camera's detection range, the system identifies and records information such as license plates, vehicle makes, colors, and simulated speeds.

## Important Dates (Reminders for us)
- November 20, 2026: presentation (5–7 minutes) (Done)
- November 24, 2026: final submission by 11:59 PM

## libs, language, and tools
- C++
- raylib 
- CMake
- GitHub Codespaces

## Running the Program

1. Open the project repository in GitHub Codespaces.
2. Open the terminal and run:

```bash
cmake -B build
cmake --build build
./build/main
```

3. Open the forwarded port `6080` to access our project.

## Collaboration (duties)
- Edgar: Deals with the car animations, physics, and some parts of the classes
- Aoanul: Fetches assets for this projects, loads them in, and creates attributes via car class. Also refactors code and documents. Oversees work of fellow peers to make sure we adhere to the hackathan requirements.
- Jeremy: Codes Collision detection, improves code for readability, separates classes into header files. 
(Workflow was flexible so we helped each other out on certain aspects)

## Research and Citations

### Flock Safety — LPR Technology
https://www.flocksafety.com/products/license-plate-readers

Researched license plate readers (LPRs) and their ability to capture license plates and vehicle characteristics, so we implemented a similar system in FlockWatch. It's more simplified, but does fetch license plate numbers.

### DeFlock — ALPR Camera Mapping
https://deflock.org/
https://maps.deflock.org/
(courtesy of Professor Blount)

Researched DeFlock's crowdsourced mapping of surveillance cameras. This gave us an idea on how to visualize our fictional Flock camera locations and detection zones on a map.

### Electronic Frontier Foundation — ALPR Privacy
https://sls.eff.org/technologies/automated-license-plate-readers-alprs

Researched the privacy implications of ALPR systems, particularly how vehicle detection records can reveal patterns of movement.

### Calculating Empires — Kate Crawford and Vladan Joler
https://calculatingempires.net/

Inspired our exploration of tech abstraction, efficiency, mass surveillance, and the relationship between technology and privacy.

### Visual Assets

- **Car artwork:** [Y8 Games — Park This Car](https://www.y8.com/games/park_this_car). Original images modified using ChatGPT.
- **Satellite imagery:** Google Earth. Took a screenshot of CCNY using this platform.
  
## Response to Calculating Empires

FlockWatch explores the relationship between technology, efficiency, and surveillance presented in *Calculating Empires*. Specifically focusing on mass surveillance and automation.

Our simulation demonstrates **abstraction** by converting vehicles into identifiable information like license plates, colors, and makes. It demonstrates **efficiency** through automated cameras capable of detecting vehicles without continuous observation from a person.

While automated surveillance can assist law enforcement, it also raises privacy concerns by enabling the collection of a drivers location. FlockWatch highlights this tradeoff between technological efficiency and personal privacy.

## Acknowledgments
Based on the starter repository provided by Professor Blount for CSC 103

Original template: https://github.com/mab253/hack2-fall26
