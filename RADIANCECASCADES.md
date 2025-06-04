A document on implementation steps to consider for implementing radiance cascades.

1. Define Ray length for probe levels.
    - Cascade 0 can for instance have length 1meters
    - Cascade 1 then have 2 meters
    - cascade 2 then has 4 meters (squared meters?)

2. Place these in the world. Define the world bounding volume
