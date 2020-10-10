const baseDir = process.cwd();

const fs = require('fs'),
    {
        promisify
    } = require('util'),
    os = require('os');

const {
    getOptions,
    request
} = require(`${baseDir}/node-libs/get`);

const writeFile = promisify(fs.writeFile);

const latitude = '37.7464',
    longitude = '-122.4442';

const RELOAD = 1000 * 60 * 60;

const API_HOSTNAME = 'api.weather.gov',
    DISCOVER_ENDPOINT = `/points/${latitude},${longitude}`;

const options = getOptions(API_HOSTNAME, DISCOVER_ENDPOINT);

async function start() {

    try {
        const props = await request(options);

        await writeFile('/tmp/forecast.json', JSON.stringify(props));

        if (!props || !props.properties || !props.properties.forecastHourly) {
            return;
        }

        if (props.properties.forecastHourly.indexOf(API_HOSTNAME) < 0) {
            return;
        }

        const newPath =  props.properties.forecastHourly.split(API_HOSTNAME)[1];
        const foptions = Object.assign({}, options, {
            path: newPath
        });
        const forecast = await request(foptions);
        await writeFile('/tmp/hourlyForecast.json', JSON.stringify(forecast));

        const updateTime = new Date(), 
            formattedDate = `${updateTime.getFullYear()}-${updateTime.getMonth() + 1}-${updateTime.getDate()}`,
            formattedTime = `${updateTime.getHours()}:${updateTime.getMinutes() + 1}`;
        let details = `Hourly: ${os.EOL}`;
        forecast.properties.periods.filter((period, index) => {
            // 4 hours only 
            return (index < 4);
        }).forEach(period => {
            const startTime = period.startTime.split('T')[1].split('-')[0].replace(/\:\d\d$/, ''),
                endTime = period.endTime.split('T')[1].split('-')[0].replace(/\:\d\d$/, '');
            details += `  (${startTime}-${endTime}): ${period.temperature}${period.temperatureUnit} / ${period.windSpeed} ${period.windDirection} ${os.EOL}`;
        });
        details += `Last Updated: ${formattedDate} @ ${formattedTime}`;

        //console.log(details);
        const err = await writeFile('/tmp/hourly.txt', details);
    } catch (e) {
        console.log(e);
    }
}

start();
setInterval(() => {
    start();
}, RELOAD);
