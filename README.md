# rshell


# Introduction
In this project, we will create a shell using design patterns we have learned in class. In particular, we have the issue of wanting to use multiple and possibly complicated expressions of commands with and/or statements. To easily evaluate this, we will construct an expression tree with the help of the composition pattern. We will also 

# Classes/Class Groups 
Base class
This will be an abstract base class which command and operator will implement:
Command - a single command with its arguments 
Operator - holds two children commands that are of the base class, so can be more operators or a command in either. The operators supported should be &&,||,>,>>,and ;.
Shell
This will be the main shell loop with the parsing logic.
Config Manager
This will deal with configuration files



# Diagram

![Alt text](https://github.com/tacalvin/rshell/blob/master/diagram.png "UML Diagram")




# Coding Strategy
We will be using version control in the form of git and github. We will slowly implement classes as well as the main shell loop slowly using branches and test our code before merging with the master branch. We will likely decide who works on what for every specific part, but in the immediate case of assignment 2 Jerry will be working with each individual operator while Calvin will be working on the command class and shell appearance.

# Roadblocks
Issues that may come up may be communication or lack of detail with regards to implementation. In addition, we are implementing things one step at a time, so it may be difficult to add in new features if we make it difficult to add them on as we go. We should attempt to keep clean and clear class roles so that the design doesn’t become too complicated for newer features.


