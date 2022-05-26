### Othello - a C++ coding demonstration

A command-line version of the classic game Othello that can be played against
another player or the computer. 

The code presented in the repository represents my answer to the following
assignment:
> Make an implementation of Othello (Reversi), in which two humans can play 
against each other, or a human against the computer. <br />
> https://en.wikipedia.org/wiki/Reversi <br />
> The evaluation of the assignment will not reward that the computer plays well.
It is sufficient, that it makes legal moves. <br />
> The implementation must demonstrate understanding of C++ and object oriented programming. <br />

I would like to stress the criteria that computer does not have to play well. As
a consequence I have implemented a very simple computer opponent.

#### Requirements

- C++ compiler
- GNU make

#### Build

0. Clone

```bash
   $ git clone https://github.com/astnn/othello.git
```

1. Compile
```bash
   $ make
```

2. Run
```bash
   $ ./othello
```

#### Inspiration
While all project code has been written from scratch I have drawn inspiration
from the following two sources:

0. [D. Roger][1]
1. [G. V. Ganesh Maurya][2]

Maurya presents a fairly straight forward object orientated solution for two
players. <br />
While Roger's solution is more complex it adds a proper computer opponent that
could serve as inspiration for upgrading the one presented in this project.

#### License

By A. S. Nielsen 2022.

All code in this repository is made available under a MIT license. Anyone is
free to use, modify, and redistribute the code under the terms of the license.
The full license is available in the file "LICENSE" at the root of the
repository.

[1]: https://github.com/drohh/othello
[2]: https://coderspacket.com/othello-game-in-c
