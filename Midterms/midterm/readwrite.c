int copy_fd(int infd, int outfd) {
  //infd and outfd are properly-opened FDs.
  //Copy all bytes from infd to outfd.
  //Return number of bytes copied.
  int buf[100], num, total = 0;
  while ((num = read(infd, buf, 100)) > 0) {
    total = total + num;
    write(outfd, buf, num);
  }
}
