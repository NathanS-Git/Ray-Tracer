# Raytracer
This is a raytracer I built in C.
All the math librarys are hand-written and thus not very performant.

## Examples

This render took about an hour to render on a Ryzen 5 1600.
The raytracer is single-threaded and not GPU accelerated (yet). So it's very slow.
Additionally, there are zero post-processing effects added, meaning every effect you see in the image below is 100% rendered.

![Raytraced scene](docs/raytrace.png)

### Tutorial

If you're interested in making this, you can check out the tutorial I used here: [_Ray Tracing in One Weekend_](https://raytracing.github.io/books/RayTracingInOneWeekend.html)

It should be noted however, the tutorial is in C++.