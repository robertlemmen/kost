Kognitiver Strukturtomograph (KOST)
===================================

This repository contains an experimental and perhaps slightly crazy framework to
visualize aspects of existing distributed systems. The basic idea is that
information about the system under analysis is collected in both an automated
and manual way and aggregated into a fact database. Based on this, further
knowledge is inferred in a generic fashion, followed by a step of
purpose- or view-specific inferring and structuring. The output of this is 
abstract but graphical/topological in nature and is then transformed into a
visual diagram in a last step:

```
  +-------------+       +-----------+       +-----------+        +-----------+       +--------+
  | Information +------->           |       |           |        | Specific  |       |        |
  |  collector  |       |           |       |           +--------> Inferring +-------> Render +--->
  +-------------+       |           |       |           |        |     +     |       |        |
                        |           |       |           |        | Transform |       |        |
  +-------------+       |           |       |           |        +-----------+       +--------+
  | Information +------->   Fact    +------->  Generic  |
  |  collector  |       | Database  |       | Inferring |
  +-------------+       |           |       |           |        +-----------+       +--------+
                        |           |       |           |        | Specific  |       |        |
  +-------------+       |           |       |           +--------> Inferring +-------> Render +--->
  |   Manual    +------->           |       |           |        |     +     |       |        |
  |   Input     |       |           |       |           |        | Transform |       |        |
  +-------------+       +-----------+       +-----------+        +-----------+       +--------+
```

## Data input

In order to collect input data, the contents of the "input.d" directory is 
examined recursively. This is done in lexicographic order, although the order 
should not matter. 

If an executable script is encountered, it is run and the output to stdout is 
captured as facts (see below). Stderr is used for logging, an exit code other 
than 0 is treated as an error. Scripts have full access to the environment,
so this is an

Non-executable scripts are just sourced as raw fact lists, so replacing an
executable script with it's stdout output would yield teh same result (in the
static case)

Outputs need to be prolog facts, and are simply concatenated together to form 
the fact database.

## Generic Inferring

XXX No idea, need to play with prolog first...

## Specific Inferring

XXX no diea, but we will need some form of common modules that can be shared

## Rendering 

the output of the specific inferring and transformation stage is a single set
of diagram entities, serialized via [HUTN]. There are a fixed number of types
and properties supported by the render stage, which are documented at XXX

[HUTN] https://www.omg.org/spec/HUTN 
