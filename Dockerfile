FROM dixaba/ubiquitous-octo-telegram:21
WORKDIR /project/build
CMD qmake /project/source && make -j $(nproc)