# milepost-feature-extractor-docker
A docker image to painlessly extract features from .c programs using MILEPOST-GCC 2.1 compiler.

### Is not necessary to clone the repo in order to use this image.
Anyway the repo contains: 
1. an alias script to ease the run of the image
2. the Dockerfile used to build the image, if needed for modifications
3. a ```test``` folder with a sample .c file to thest the image
So it can be useful to clone the repo.
```
git clone https://github.com/lulogit/milepost-feature-extractor-docker.git
```
## The image
The docker image is available on [Docker Hub](https://hub.docker.com/r/lullo/milepost-feature-extractor/).
It can be pulled via ```docker pull lullo/milepost-feature-extractor```.


## Usage
The simplest way to run the *docker image* is via the provided *alias script*:
```
# once cloned the repo or downloaded the alias.sh script
source alias.sh # load the 'mp_feat_ex' alias
cd /test
mp_feat_ex
# now all features are in the (created) 'feature' folder
```
Alternatively is possible to run the image through the ```docker run``` command:
```
sudo docker run --mount type=bind,src=$(pwd),dst=/sources -ti lullo/milepost-feature-extractor:slim
sudo chown $(id -u) ./features* # files created by the docker image are owned by 'root' user by default
```
The ```chown``` command is used to restore the ownership of the createted 'feature' folder to the current user. This due to the fact that docker's mounted files are owned by 'root' by default.

In both cases the extractor will:
1. analyze the .c source files present in the current path
2. save the files containing the extracted features (.ft) for every function in the program, in the ```features``` directory


## Dependencies
Since it is a docker image, having docker installed is a prerequisite.
See the [official docker installation guide](https://docs.docker.com/install/) for an in-detail discussion of the installation process on many different operative systems.
On *Ubuntu* it can be installed via the package manage:
```
apt-get install docker.io
```

## Dockerfile and build process
The Dockerfile provided in this repo can be used to build the image. This is not useful since the image is already available on Docker Hub. However is extremely useful in order to obtain a **slightly modified version of the image**.
In fact the image execute a custom script that just extract features from .c source files. But the image contains a full installation of MILEPOST GCC 2.1 and CTUNING-CC 2.5 (on which the feature extractor is based). So in order to fully exploit these tools, or customize the script, is suggested to modify the ```Dockerfile```.

### The ```--squash``` flag
Is important to notice that each command (RUN, COPY, ENV, ...) in the Dockerfile correspond to a layer, and each layer store the difference with respect to the previous layer in the image. This lead to huge image sizes when some file are created in one layer and deleted in another (is stored twice as difference). To avoid this the image was built using the ```--squash``` flag of ```docker run```. This merge all the layers together and produce an tiny image (files created in one layer and deleted in another are not included).

### Building the image
The image can be built by entering in the folder with the *Dockerfile* and running:
```
docker build --squash -t myimagetag .
```
The **tag** is a human readable name that can be used to reference that image thereafter (e.g: lullo/milepost-feature-extractor).

## Purpose
Feature extraction is extremely useful in order to train the selection of compiler flags, in a machine learning setting.
This renders possible to automaticcaly optimize the compilation process by setting the flags that best fit the program features.

## The features
As reported from [the official MILEPOST GCC 2.1 features description](http://ctuning.org/wiki/index.php/CTools:MilepostGCC:StaticFeatures:MILEPOST_V2.1), these are the supported features for different extractor files.

<a name="File_featlstn.P_-_55_features_.28removed_duplicate_feature_ft21.29"></a><h3> <span class="mw-headline"> File <i><b>featlstn.P</b></i> - 55 features (removed duplicate feature ft21) </span></h3>
<table cellspacing="0" cellpadding="5" border="1">

<tbody><tr>
<td> ft1
</td><td> Number of basic blocks in the method
</td></tr>
<tr>
<td> ft2
</td><td> Number of basic blocks with a single successor
</td></tr>
<tr>
<td> ft3
</td><td> Number of basic blocks with two successors
</td></tr>
<tr>
<td> ft4
</td><td> Number of basic blocks with more then two successors
</td></tr>
<tr>
<td> ft5
</td><td> Number of basic blocks with a single predecessor
</td></tr>
<tr>
<td> ft6
</td><td> Number of basic blocks with two predecessors
</td></tr>
<tr>
<td> ft7
</td><td> Number of basic blocks with more then two predecessors
</td></tr>
<tr>
<td> ft8
</td><td> Number of basic blocks with a single predecessor and a single successor
</td></tr>
<tr>
<td> ft9
</td><td> Number of basic blocks with a single predecessor and two successors
</td></tr>
<tr>
<td> ft10
</td><td> Number of basic blocks with a two predecessors and one successor
</td></tr>
<tr>
<td> ft11
</td><td> Number of basic blocks with two successors and two predecessors
</td></tr>
<tr>
<td> ft12
</td><td> Number of basic blocks with more then two successors and more then two predecessors
</td></tr>
<tr>
<td> ft13
</td><td> Number of basic blocks with number of instructions less then 15
</td></tr>
<tr>
<td> ft14
</td><td> Number of basic blocks with number of instructions in the interval [15, 500]
</td></tr>
<tr>
<td> ft15
</td><td> Number of basic blocks with number of instructions greater then 500
</td></tr>
<tr>
<td> ft16
</td><td> Number of edges in the control flow graph
</td></tr>
<tr>
<td> ft17
</td><td> Number of critical edges in the control flow graph
</td></tr>
<tr>
<td> ft18
</td><td> Number of abnormal edges in the control flow graph
</td></tr>
<tr>
<td> ft19
</td><td> Number of direct calls in the method
</td></tr>
<tr>
<td> ft20
</td><td> Number of conditional branches in the method
</td></tr>
<tr>
<td> ft21
</td><td> Number of assignment instructions in the method
</td></tr>
<tr>
<td> ft22
</td><td> Number of binary integer operations in the method
</td></tr>
<tr>
<td> ft23
</td><td> Number of binary floating point operations in the method
</td></tr>
<tr>
<td> ft24
</td><td> Number of instructions in the method
</td></tr>
<tr>
<td> ft25
</td><td> Average of number of instructions in basic blocks
</td></tr>
<tr>
<td> ft26
</td><td> Average of number of phi-nodes at the beginning of a basic block
</td></tr>
<tr>
<td> ft27
</td><td> Average of arguments for a phi-node
</td></tr>
<tr>
<td> ft28
</td><td> Number of basic blocks with no phi nodes
</td></tr>
<tr>
<td> ft29
</td><td> Number of basic blocks with phi nodes in the interval [0, 3]
</td></tr>
<tr>
<td> ft30
</td><td> Number of basic blocks with more then 3 phi nodes
</td></tr>
<tr>
<td> ft31
</td><td> Number of basic block where total number of arguments for all phi-nodes is in greater then 5
</td></tr>
<tr>
<td> ft32
</td><td> Number of basic block where total number of arguments for all phi-nodes is in the interval [1, 5]
</td></tr>
<tr>
<td> ft33
</td><td> Number of switch instructions in the method
</td></tr>
<tr>
<td> ft34
</td><td> Number of unary operations in the method
</td></tr>
<tr>
<td> ft35
</td><td> Number of instruction that do pointer arithmetic in the method
</td></tr>
<tr>
<td> ft36
</td><td> Number of indirect references via pointers ("*" in C)
</td></tr>
<tr>
<td> ft37
</td><td> Number of times the address of a variables is taken ("\&amp;" in C)
</td></tr>
<tr>
<td> ft38
</td><td> Number of times the address of a function is taken ("\&amp;" in C)
</td></tr>
<tr>
<td> ft39
</td><td> Number of indirect calls (i.e. done via pointers) in the method
</td></tr>
<tr>
<td> ft40
</td><td> Number of assignment instructions with the left operand an integer constant in the method
</td></tr>
<tr>
<td> ft41
</td><td> Number of binary operations with one of the operands an integer constant in the method
</td></tr>
<tr>
<td> ft42
</td><td> Number of calls with pointers as arguments
</td></tr>
<tr>
<td> ft42
</td><td> Number of calls with the number of arguments is greater then 4
</td></tr>
<tr>
<td> ft44
</td><td> Number of calls that return a pointer
</td></tr>
<tr>
<td> ft45
</td><td> Number of calls that return an integer
</td></tr>
<tr>
<td> ft46
</td><td> Number of occurrences of integer constant zero
</td></tr>
<tr>
<td> ft47
</td><td> Number of occurrences of 32-bit integer constants
</td></tr>
<tr>
<td> ft48
</td><td> Number of occurrences of integer constant one
</td></tr>
<tr>
<td> ft49
</td><td> Number of occurrences of 64-bit integer constants
</td></tr>
<tr>
<td> ft50
</td><td> Number of references of a local variables in the method
</td></tr>
<tr>
<td> ft51
</td><td> Number of references (def/use) of static/extern variables in the method
</td></tr>
<tr>
<td> ft52
</td><td> Number of local variables referred in the method
</td></tr>
<tr>
<td> ft53
</td><td> Number of static/extern variables referred in the method
</td></tr>
<tr>
<td> ft54
</td><td> Number of local variables that are pointers in the method
</td></tr>
<tr>
<td> ft55
</td><td> Number of static/extern variables that are pointers in the method
</td></tr></tbody></table>
<a name="File_featlstn1.P_-_56_features_.28move_duplicate_feature_to_ft56.29"></a><h3> <span class="mw-headline"> File <i><b>featlstn1.P</b></i> - 56 features (move duplicate feature to ft56) </span></h3>
<table cellspacing="0" cellpadding="5" border="1">

<tbody><tr>
<td> ft56
</td><td> Number of unconditional branches in the method
</td></tr></tbody></table>
<a name="File_featlstn2.P_-_65_features_.28ft57-65_features_have_been_added_by_Jeremy_Singer.29"></a><h3> <span class="mw-headline"> File <i><b>featlstn2.P</b></i> - 65 features (ft57-65 features have been added by Jeremy Singer) </span></h3>
<table cellspacing="0" cellpadding="5" border="1">

<tbody><tr>
<td> ft57
</td><td>
<pre>CYCLOMATIC COMPLEXITY
N == number of return instrs in fn
N1 == number of cond instrs in fn
N2 == N1-N
N3 == N2+2. definition of cyclomatic complexity from:
<a href="http://en.wikipedia.org/wiki/Cyclomatic_complexity" class="external free" title="http://en.wikipedia.org/wiki/Cyclomatic_complexity" rel="nofollow">http://en.wikipedia.org/wiki/Cyclomatic_complexity</a>
</pre>
</td></tr>
<tr>
<td> ft58
</td><td>
<pre>Jeremy Singer addition:
HALSTEAD's METRICS described at <a href="http://en.wikipedia.org/wiki/Halstead_complexity_measures" class="external free" title="http://en.wikipedia.org/wiki/Halstead_complexity_measures" rel="nofollow">http://en.wikipedia.org/wiki/Halstead_complexity_measures</a>
</pre>
<pre>HN2 is total number of operands (Halstead N2)
</pre>
</td></tr>
<tr>
<td> ft59
</td><td> Hn2 is number of distinct operands (Halstead n2)
</td></tr>
<tr>
<td> ft60
</td><td> N is num var defs (should be == Halstead n2 or Halstead N2?)
</td></tr>
<tr>
<td> ft61
</td><td> HN1 is total number of operators (Halstead N1) (approx due to abstraction)
</td></tr>
<tr>
<td> ft62
</td><td> Hn1 is number of distinct operators (Halstead n1) (approx due to abstraction)
</td></tr>
<tr>
<td> ft63
</td><td>
<pre>approx of Halstead difficulty D == Hn1/2 * (HN2 / Hn2)
(NB uses the aver routine to avoid problems with 0 divisor in
computation of HN2/Hn2)
</pre>
</td></tr>
<tr>
<td> ft64
</td><td>
<pre>approx of Halstead volume
volume == HN *log_2(Hn)
where HN == HN1+HN2
and Hn == Hn1+Hn2
</pre>
</td></tr>
<tr>
<td> ft65
</td><td>
<pre>approx of Halstead effort, which
== Difficulty * Volume
</pre>
</td></tr></tbody></table>
