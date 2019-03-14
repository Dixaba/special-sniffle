FROM dixaba/ubiquitous-octo-telegram:21
CMD ["bash", "-c", "cd /project/build && qmake /project/source && make -j $(nproc)" ]