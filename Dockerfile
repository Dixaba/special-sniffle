FROM dixaba/ubiquitous-octo-telegram:21
WORKDIR /project/build
RUN ls -l .
RUN qmake /project/source 
RUN make -j $(nproc)