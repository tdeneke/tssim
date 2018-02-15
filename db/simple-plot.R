data = scan('1518703301-0');
data_sim = scan('1518703301-0-sim');
plot(data, type="l");
lines(data_sim, type="l", col="red");
dev.copy(png,'ts.png');
dev.off();
