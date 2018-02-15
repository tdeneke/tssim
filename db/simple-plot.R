data = scan('1518680378-0');
plot(data, type="l");
dev.copy(png,'ts.png');
dev.off();
