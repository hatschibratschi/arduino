#install.packages(c('plumber'))
library(plumber)

plumb("plumber/plumber.R") %>% 
  pr_run(host="0.0.0.0",  port = 5762)

#(resp <- httr::GET("localhost:5762/echo?msg=Hello")) 

if(FALSE){
  # read text-file
  d = read.csv(file = 'plumber/data.csv', header = FALSE)
  # header
  names(d) = c('device', 'sensor', 'value', 'datetime')
  # convert datetime
  d$datetime = strptime(d$datetime, format="%Y-%m-%d %H:%M:%S")
  # plot
  plot(x = d$datetime, y = d$value)
  
  # http://127.0.0.1:5762/saveSensorValue?device=arduino2&sensor=water&value=41

  # curl -X POST "http://127.0.0.1:5762/saveSensorValue?device=arduino2&sensor=water&value=33" -H  "accept: */*" -d ""
}