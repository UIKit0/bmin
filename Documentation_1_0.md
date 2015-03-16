# Bmin 1.0 #



## Installation ##

Application is supported for Windows and Linux. The installation depends on the platform.

### Windows ###

For Windows the installer [bmin-1.0.1-win32.exe](http://bmin.googlecode.com/files/bmin-1.0.1-win32.exe) is
available. After executing the installer it is necessary to agree to the GPL version 3 license agreement. Then it is
possible to create a shortcut in the `Start menu` as well as on the desktop. It is also possible to choose the install
location (default is set to `C:\Program Files\Bmin`) and the name of the folder in the Start menu (default is
`Bmin`). After installing the application it can be launched straight from the installer.

During the installation the uninstaller is simultaneously created. The uninstaller is located in the same folder where
the application was installed and called `Bmin Uninstall`. When creating a folder in the Start menu the uninstallation
shortcut is located here.


### Linux ###

It is necessary to download the source code for Linux [bmin-1.0.1.tgz](http://bmin.googlecode.com/files/bmin-1.0.1.tgz) . The application depends on Qt library. This requires at least version 4.5 (version earlier than 4.5
will probably not compile). Qt library must be installed even if the application only runs in a shell mode. The Mesa
library version 7.8 (or later) and xorg-server version 1.7 or later must be also installed.

First, you need to unpack the gzip archive. The translation is done in two steps. First, in the directory with unpacked
source code, run the `configure file`. It creates a `Makefile` and it can pass the arguments presented in the following
table.

| **Option** | **Description** |
|:-----------|:----------------|
| `--prefix=PATH` | Set installation directory prefix. Default value is `/usr` |
| `--bindir=PATH` | Set directory containing the application files Default value  $PREFIX/usr`, where `$PREFIX` is installation directory prefix. |

After creating a `Makefile` you need to call the `make` command and then `make install` to save the executable file bmin
into place. The whole process might look like this:

```
# tar -xzf bmin-1.0.1.tgz
# cd bmin-1.0.1
# ./configure --prefix=/usr/local
# make
# make install
# bmin
```

The last command applies only if the program is intended to run in GUI mode.


### Executing ###

The application has two modes. The first is the **Qt GUI mode** and the second is **Shell mode** that can be run using the
option `--shell` or short `-s`. The Shell mode is available only for Linux. You can specify the startup option `--help`
or `-h` for short which displays help. The last option is the `--version` or `-v` for short that displays the version
number.


## Qt GUI mode ##

As the name suggests, the **Qt GUI mode** is executing in a graphical environment. After its launch it displays the main
window with the menu bar, the main layout and the status bar. The main layout is divided into two parts - **top** and
**bottom**.

The **top part** is used for setting a Boolean function in its complete form and displaying the resulting minimized form
of the function. The function can be entered directly into a text box or it can be used to create a function wizard (see
below), which appears when you click on the button `New...`. If the specified function is set then the button `New...`
is changed to `Edit...` and after clicking on it the function can be edited. The representation of logic functions can
be set in a selection box `Representation of logic function:` where is the choice of the `Sum of Products`, which is a
**DNF** (Disjunctive Normal Form), and `Products of Sums`, which is a **CNF** (Conjunctive Normal Form). The `Minimize`
button is used to start the minimization. The resulting minimized function is displayed in the box `Minimal form:` which
is read only.

The **bottom part** contains four buttons on the left side. They are used for switching mode. The name of each mode is
written on the button. The button with the current mode has black letters on white background. The easiest way to switch
modes is to click on the button. The graphical application has four modes. The first is the Welcome mode which allows
you to select another mode or open the About dialog. The other three modes are used for demonstration of the
minimization of Boolean functions. Specifically, the Karnaugh map (K-map), the Boolean n-cube and of course the
Quine-McCluskey algorithm. The following subsections describe how to set the Boolean function, above modes and some
other functions.


### Setting Boolean function ###

#### Direct setting ####

Setting the function into the text field can take two forms. In the case of the Sum of Products representation the form
is following:

```
f(variable_list) = sum m(on_set) [ + sum d(dont_care_set)]
```

where `variable_list` is the comma separated list of letters and `on_set` and `dont_care_set` are lists of numbers
separated by commas. The list `on_set` is used to place the indexes of minterms with output value `1` (true state) and
the list `dont_care_set` is for minterms whose output value is irrelevant (it is a forbidden state and such term is
called don't care term). Square brackets indicate that the setting of these states is optional. But setting the true
states is always required. If the function contains only false states then the list is empty. It writes as `m()`. Extra
spaces and tabs are ignored. The specified function may therefore have the following form:

```
f(d,c,b,a) = sum m(1,3,5,12,13) + sum d(2,10)
```

In the case of Product of Sums representation the form is following:

```
f(variable_list) = prod m(off_set) [ * prod d(dont_care_set)]
```

Everything is basically the same as the Sum of Products representation, up to the fact that there are no minterms but
maxterms, the middle sign is `*` instead of `+` and the list `off_set` is a comma separated list of indexes of the
maxterms with output value `0` (false state).

#### Creating wizard ####

There is also a wizard for creating a logic function. The top four items are for setting the function name, selecting a
representation and the number of variables and possibly enter the names of variables. After setting the number of
variables the truth table is generated. There it is possible to change the output values in the column titled `Output`
in several ways. The first way is by double clicking on the cell in the `Output` column and then a combo box will
appear, and from there you can select the desired output value. The second way is selecting the desired output cell and
then pressing the key with desired value (for example pressing key `1` for changing to output value 1). Another way is
selecting the group of output cells and then open the context menu by clicking the right mouse button. There it is
possible to set the output values for selected or all output values. The function is saved by clicking on the `OK`
button (or pressing `Enter` on the keyboard). Alternatively the function can be canceled by pressing the `Cancel` button
(or pressing `Escape` on the keyboard).

### Karnaugh map ###

The Karnaugh map is a tool for minimizing logic functions. It can be described as a two-dimensional array whose values
are either 1 (true state) or 0 (false state) or X (forbidden state). The position of each value is determined by the
state of the function. It means that the position is uniquely determined for each minterm (maxterm) so that the minterms
(maxterms) which differ in one variable are neighboring cells on the map. It makes it possible to cover all minimal
terms. A more detailed description can be found on [Wikipedia.org](http://en.wikipedia.org/wiki/Karnaugh_map).

The Karnaugh map in Bmin is drawn up to **6 variables**. The layout is divided into two parts. The left side displays the
map and the right side displays the lists for displaying minterms (maxterms) and covers (more specifically terms of
minimum coverage). These are only displayed if the checkbox `Show Covers` is marked. The map is drawn once the function
is set. There are two modes for the description of variables. The first shows the distribution in binary form and the
second shows lines representing negations. Modes can be changed in the context menu by right clicking on the description
of variables. You can also change the output values of terms by left clicking on the appropriate place on the map. The
map changes are also directly displayed in the assignment of functions in the text box. The map is also linked with the
list of the minterms (maxterms) and covers on the right side. Each selected minterm (maxterm) will change background
color on its position on the map. Each selected cover highlights all minterms (maxterms) which are covered by it. The
covers are also marked on the map using color boxes. The form of terms depends on the representation of the
function. Accordingly, it also determines whether the terms are minterms or maxterms.

### Boolean n-cube ###

The Boolean n-cube is often called hypercube. It is an n-dimensional analogue of a square (n = 2), a cube (n = 3) and a
tesseract (n = 4). The number of dimensions is equal to the number of variables and the number of vertexes is equal to
the number of minterms (maxterms). Every neighboring minterms (maxterms), which differs in only one variable, are
connected by an edge.

The Boolean n-cube in Bmin is created using OpenGL. Therefore, the n-cube is displayed in 3D space and offers two
views. The first is the 3D view which allows you to browse inside the cube. The second is the Rotating view which allows
you to rotate with the n-cube. You can view a n-cube up to a maximum of **3 variables**. The vertexes are shown as spheres
and the minterms (maxterms) with the same output value have the same color. So they are defined as three colors for each
output value one:
  * <font color='cyan'>cyan</font> - false state
  * <font color='red'>red</font> - true state
  * <font color='magenta'>magenta</font> - forbidden state

The edges connecting the vertices are displayed as a tight cylinder. Minimized terms are clearly displayed as the yellow
loop-line which circulates the covered minterms (maxterms).

#### Control ####

Boolean n-cube can be controlled only if it is active. The user can use both the mouse and keyboard.

The output value of the minterm (maxterm) can be changed by left clicking the mouse. In addition, the context menu can
be opened by right clicking the mouse. The following table lists the various menu items and their description:

| **Item** | **Description** |
|:---------|:----------------|
| `Camera` | Allows you to select one of two views - 3D view (`3D`) Rotating view (`Rotated`).  |
| `Lights` | Allows you to determine which lights will be lit. There is one special source light for 3D view. The name of this light is reflector (`Reflector`). In addition, there are two indicator lights - front (`Light 1`) and back (`Light 2`). |

Using the keyboard you can control many different elements. Options are divided into three groups. First, a common
option for both views and the options that are specific to the concrete view. The following table describes in detail
all of the options.

**Table of common options:**

| **Key** | **Description** |
|:--------|:----------------|
| `1` | Set 3D view  |
| `2` | Set Rotate view  |
| `L` | Automatic motion of lights |
| `C` | Show / Hide the loops of the minimized terms |

**Table of 3D view options:**

| **Key** | **Description** |
|:--------|:----------------|
| `W (forward arrow)` |  move forward|
| `S (back arrow)` | move backward |
| `A (left arrow)` | turn left |
| `D (right arrow)` | turn right |
| `E (Page Up)` | turn up |
| `X (Page Down)` | turn down |
| `T` | move up |
| `G` | move down |
| `F` | move left |
| `H` | move right |
| `R` | turn on the reflector |

**Table of Rotating view options:**

| **Key** | **Description** |
|:--------|:----------------|
| arrows | rotating of the n-cube  |
| `+` | zoom in the n-cube |
| `-` | zoom out the n-cube |
| `R` | automatic rotation |


The layout is divided into two parts as well as the layout for the Karnaugh map. It is possible to select minterms
(maxterms) and covers which are connected to the n-cube.


### Running of the Quine-McCluskey algorithm. ###

The Quine-McCluskey algorithm is one of the most known algorithms for minimizing logic function. Its description is out
of scope in this manual. The detailed description can be found at
[Wikipedia.org](http://en.wikipedia.org/wiki/Quine-McCluskey_algorithm).

This mode in Bmin shows the statement of running of the Quine-McCluskey algorithm. There is the table which shows the
finding of prime implicants and the covering table. When you change the function the tables reflect this change
automatically. The chosen minimized terms naturally depend on the representation of the function.


### Top menu bar ###

The top menu contains two menus - `File` and `Help`. The `Help` menu contains only one action About Bmin which opens the
`About dialog`. The dialog shows basic information about Bmin and the GPL version 3 license agreement. More interesting
is the `File` menu. This menu contains several actions that are reported below. There are all the items, including the
shortcuts which alternatively invoke the action and descriptions of all actions. It should be noted that it can be
created with more output functions by loading PLA file. In the case when the dialogue is displayed one selection must be
made, which becomes the current function. It is because Bmin supports only single output value functions. In addition,
note that the file which contains program settings is in a hidden directory `config` in the user's home directory. This
setting is used to `Store` and `Load` actions.

| **Item** | **Shortcut** | **Description** |
|:---------|:-------------|:----------------|
| `New...` | `Ctrl+N` | Invoke a dialog for creating a new logic function.  |
| `Edit...` | `Ctrl+E` | Invoke a dialog for editing a new logic function (only if the current function is set).  |
| `Open...` | `Ctrl+O` | Load logic function from PLA file, which is chosen from the open file dialog.  |
| `Save as...` | `Ctrl+S` | Save the current function to the PLA file. The path is chosen in the save file dialog. |
| `Load` | `Ctrl+L` | Load current function from the settings.  |
| `Store` | `Ctrl+W` | Save the current function to the settings.  |
| `Exit` | `Ctrl+Q` | Exit the Bmin.  |


## Shell mode ##

The second mode is the **Shell mode**, which is available only for Linux, started when you set the command line option
`-s` or `--shell`. It is a terminal application which after its launch shows a few lines about the rights and license
agreement and then prints out the line starting with character '`>`'. It symbolizes the command line, where you can type
the commands described below or set the function. This is done in the same way as described in the section Direct
setting. After writing the function it is necessary to press `Enter` to set the function as current.

### Commands ###

All commands are listed in the following table. A special command is the show that takes one or zero argument. Each
argument is therefore placed in a separate box in the table.

| **Command** | **Description** |
|:------------|:----------------|
| `exit` | Exit the Bmin. |
| `minimize` | Minimize the current logic function. |
| `qm` | Switch the minimizing algorithm to Quine-McCluskey. |
| `espresso` | Switch the minimizing algorithm to Espresso.  |
| `sop` | Set representation of the logic function to DNF (Disjunctive Normal Form). |
| `pos` | Set representation of the logic function to CNF (Conjunctive Normal Form).  |
| `show` | Show the current logic function.  |
| `show qm` | Show running of the Quine-McCluskey algorithm. |
| `show espresso` | Show running of the Espresso algorithm.  |
| `show kmap` | Show the Karnaugh map  |