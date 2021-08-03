# Modern c++ Course

This repository hosts my solutions to the [problems](https://www.ipb.uni-bonn.de/teaching/cpp-2020/homeworks/) on the modern c++ for computer vision and image proccessing [course](https://www.youtube.com/playlist?list=PLgnQpQtFTOGRM59sr3nSL8BmeMZR9GCIA) made by [Cyrill Stachniss](https://github.com/stachnis) and [Ignacio Vizzo](https://github.com/nachovizzo) at the University of Bonn. They own all the credits for the problems formulation and material.

Thanks to them and to the University for posting this material and all the other courses online for free.

## Homework 2

To test this homework follow these instructions:

1. Locate yourself inside the `/homework_2` folder, create a `/bin` folder and cd into it; rhen run cmake and build the project. To do all this at once type on a terminal in the main folder:

    ```.sh
    cd homework_2 && mkdir -p bin && cd bin && cmake .. && make && cd ..
    ```

2. The executables `./task_a` and `./task_b` will be created inside the `/bin` folder. You can run them like its stated in the homework description:

    ```.sh
    ./bin/task_2 100.txt 200.txt
    ```

## Homework 3

To test this homework follow these instructions:

1. Locate yourself inside the `/homework_3` folder, create a `/bin` folder and cd into it; rhen run cmake and build the project. To do all this at once type on a terminal in the main folder:

    ```.sh
    cd homework_3 && mkdir -p bin && cd bin && cmake .. && make && cd ..
    ```

2. The executable `./create_image_browser` will be created inside the `/bin` folder. You can run it like its stated in the homework description:

    ```.sh
    ./bin/create_image_browser > web_app/test.html && xdg-open web_app/test.html
    ```

## K-Means C++ implementation

For the `homework_7` a k-means algorithm was implemented in the [bow.cpp](homework_7/src/bow.cpp). It can be seen in action in the image below:

![ Alt text](/docs/k_means.gif)
