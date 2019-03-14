FROM dixaba/ubiquitous-octo-telegram:21
RUN chmod 777 run.sh
CMD ["/run.sh"]