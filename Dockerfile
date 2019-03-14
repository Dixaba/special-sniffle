FROM dixaba/ubiquitous-octo-telegram:21
COPY run.sh /tmp/run.sh
CMD ["bash", "/tmp/run.sh"]