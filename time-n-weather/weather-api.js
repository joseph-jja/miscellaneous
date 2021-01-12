const baseDir = process.cwd();

const fs = require('fs'),
    {
        promisify
    } = require('util'),
    os = require('os');

const asyncwrapper = require(`${baseDir}/node-libs/asyncWrapper`),
    {
        getOptions,
        request
    } = require(`${baseDir}/node-libs/get`),
    {
        formatTime,
        formatDate
    } = require(`${baseDir}/node-libs/format.js`);

const writeFile = promisify(fs.writeFile);

const latitude = '37.7464',
    longitude = '-122.4442';

const RELOAD = 1000 * 60 * 60;

const API_HOSTNAME = 'api.weather.gov',
    DISCOVER_ENDPOINT = `/points/${latitude},${longitude}`;

const options = getOptions(API_HOSTNAME, DISCOVER_ENDPOINT);

async function start() {

    const [rerr, props] = await asyncwrapper(request(options));
    if (rerr) {
        return;
    }

    await writeFile('/tmp/forecast.json', JSON.stringify(props));

    if (!props || !props.properties || !props.properties.forecastHourly) {
        return;
    }

    if (props.properties.forecastHourly.indexOf(API_HOSTNAME) < 0) {
        return;
    }

    const newPath = props.properties.forecastHourly.split(API_HOSTNAME)[1];
    const foptions = Object.assign({}, options, {
        path: newPath
    });
    const [ferr, forcast] = await asyncwrapper(request(foptions));
    if (ferr) {
        return;
    }
    await writeFile('/tmp/hourlyForecast.json', JSON.stringify(forecast));

    const updateTime = new Date(),
        formattedDate = formatDate(updateTime),
        formattedTime = formatTime(updateTime);
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
}

start();
setInterval(() => {
    start();
}, RELOAD);
