FROM ubuntu:16.04
COPY run.sh /tmp/run.sh
RUN chmod 777 /tmp/run.sh
CMD ["/tmp/run.sh"]