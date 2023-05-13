# Pull request; by: Baller Baller

## Commit "Fixed flickering bug in audio visualizer"

- Updated frequency `updateFrequency` changed from 5 to 60
- Updated upper limit `topBorder` from -69 to 200

## Commit "Fixed memory leak in engine unitialization"

- Added `free(&engine)` in line 47 of file `start-engine.c`.