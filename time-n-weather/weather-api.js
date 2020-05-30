const baseDir = process.cwd();

const fs = require('fs'),
    os = require('os');

const {
    getOptions,
    request
} = require(`${baseDir}/node-libs/get`);

const latitude = '37.7464',
    longitude = '-122.4442';

const RELOAD = 1000 * 60 * 60;

const API_HOSTNAME = 'api.weather.gov',
    DISCOVER_ENDPOINT = `/points/${latitude},${longitude}`;

const options = getOptions(API_HOSTNAME, DISCOVER_ENDPOINT);

async function start() {

    const props = await request(options);

    options.path = props.properties.forecastHourly.split(API_HOSTNAME)[1];
    const forecast = await request(options);
    //console.log(forecast);

    let details = `Hourly: ${os.EOL}`;
    forecast.properties.periods.filter((period, index) => {
        // 8 hours only 
        return (index < 8);
    }).forEach(period => {
        const startTime = period.startTime.split('T')[1].split('-')[0],
            endTime = period.endTime.split('T')[1].split('-')[0];
        details += `  (${startTime}-${endTime}): ${period.temperature}${period.temperatureUnit} / ${period.windSpeed} ${period.windDirection} ${os.EOL}`;
    });

    //console.log(details);
    fs.writeFile('/tmp/hourly.txt', details, (errx) => {
        // TODO handle error?
    });
}

start();
setInterval(() => {
    start();
}, RELOAD);
