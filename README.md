# Modern C++ Course Homeworks

This repository hosts my solutions to the [problems](https://www.ipb.uni-bonn.de/teaching/cpp-2020/homeworks/) on the modern c++ for computer vision and image proccessing [course](https://www.youtube.com/playlist?list=PLgnQpQtFTOGRM59sr3nSL8BmeMZR9GCIA) made by [Cyrill Stachniss](https://github.com/stachnis) and [Ignacio Vizzo](https://github.com/nachovizzo) at the University of Bonn. They own all the credits for the problems formulation and material.

Thanks to them and to the University for posting this material and all the other courses online for free.

**DISCLAIMER**: I have not run the provided tests (yet).

## Dependencies

to work and build the files provided in this repo you need to install the following dependencies:

### Ubuntu 20.04

To easily install alongisde Windows you can follow this [tutorial](https://itsfoss.com/install-ubuntu-1404-dual-boot-mode-windows-8-81-uefi/). The `clang` compiler should be preinstalled in this distro, however is probably a good idea to run this [script](https://raw.githubusercontent.com/wiki/nachovizzo/must-have-tools/scripts/install_llvm_toolchain.sh) to make sure you have the toolchain suggested by [Ignacio Vizzo](https://github.com/nachovizzo) for the homeworks.

### Visual Studio Code (Recommended)

I used VScode to work on this repo. To install it and use the suggested extensions and configuration you can follow these [instructions](https://github.com/nachovizzo/must-have-tools/wiki#modern-text-editors) by [Ignacio Vizzo](https://github.com/nachovizzo)

### OpenCV

Its a compile dependency for several homeworks. Its neccessary to have the full version of OpenCV to use the `sift` feature extractor. To install `OpenCV` the same way as I did you can follow these [instructions](https://github.com/nachovizzo/example_opencv#prerequisites) by [Ignacio Vizzo](https://github.com/nachovizzo).

### libpng++

Its a compile dependency for `homework_8`. You can install it using the package manager:

```.sh
sudo apt install libpng++-dev
```

## Code Insights

### Homework 2

To test this homework follow these instructions:

1. Locate yourself inside the `/homework_2` folder, create a `/bin` folder and cd into it; rhen run cmake and build the project. To do all this at once type on a terminal in the main folder:

    ```.sh
    cd homework_2 && mkdir -p bin && cd bin && cmake .. && make && cd ..
    ```

2. The executables `./task_a` and `./task_b` will be created inside the `/bin` folder. You can run them like its stated in the homework description:

    ```.sh
    ./bin/task_2 100.txt 200.txt
    ```

### Homework 3

To test this homework follow these instructions:

1. Locate yourself inside the `/homework_3` folder, create a `/bin` folder and cd into it; rhen run cmake and build the project. To do all this at once type on a terminal in the main folder:

    ```.sh
    cd homework_3 && mkdir -p bin && cd bin && cmake .. && make && cd ..
    ```

2. The executable `./create_image_browser` will be created inside the `/bin` folder. You can run it like its stated in the homework description:

    ```.sh
    ./bin/create_image_browser > web_app/test.html && xdg-open web_app/test.html
    ```

### K-Means C++ implementation

For the `homework_7` a k-means algorithm was implemented in the [bow.cpp](homework_7/src/bow.cpp). It can be seen in action in the image below:

![ Alt text](/docs/k_means.gif)

Later in `homework_9` this functionality was implemented using the `flann`  implementation provided by `OpenCV`. This increased its execution speed significantly. 
