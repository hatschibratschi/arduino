library(plumber)

file = 'data.csv'

#* @apiTitle Plumber sensor API
#* @apiDescription send sensor data and view a plot.

#* Plot data
#* @serializer png
#* @get /plot
function() {
  d = read.csv(file = file, header = FALSE)
  # header
  names(d) = c('device', 'sensor', 'value', 'datetime')
  # convert datetime
  d$datetime = strptime(d$datetime, format="%Y-%m-%d %H:%M:%S")
  # plot line
  plot(x = d$datetime
       , y = d$value
       , type = 'l'
       , main = 'watersensor'
       , xlab = 'datetime'
       , ylab = 'water')
}

#* save sensor data of device to file
#* @param device device name. eg. arduino2
#* @param sensor sensor. eg. water
#* @param value value of the sensed data. eg. 34
#* @post /saveSensorValue
function(device, sensor, value) {
  cat(paste0(device, ',', sensor, ',', value, ',', Sys.time())
      , file=file
      , append=TRUE
      , sep = "\n")
  list(msg = paste0('device: ', device, ' sensor: ', sensor, ' value: ', value, ' was saved to file ', file))
}

