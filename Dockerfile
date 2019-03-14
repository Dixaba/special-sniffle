FROM dixaba/ubiquitous-octo-telegram
WORKDIR /project/build
CMD qmake /project/source && make -j $(nproc)