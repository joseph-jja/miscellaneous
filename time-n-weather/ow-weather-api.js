const baseDir = process.cwd();

const os = require('os'),
    fs = require('fs'),
    {
        promisify
    } = require('util');

const asyncwrapper = require(`${baseDir}/node-libs/asyncWrapper`),
    {
        getOptions,
        request
    } = require(`${baseDir}/node-libs/get`),
    {
        formatTime,
        formatDate
    } = require(`${baseDir}/node-libs/format.js`);

const readFile = promisify(fs.readFile);

const hostname = os.hostname();

const latitude = '37.7464',
    longitude = '-122.4442';

const API_HOSTNAME = 'api.openweathermap.org',
    DISCOVER_ENDPOINT = `/data/2.5/weather?lat=${latitude}&lon=${longitude}`;

const RELOAD = 1000 * 60 * 60;

function toFahrenheit(kelvin) {
    return `${Math.round(9 / 5 * kelvin - 459.67)}F`;
}

async function start() {

    //const results = require('/tmp/full.js');
    const keyFile = await readFile(`${baseDir}/config.json`);
    key = JSON.parse(keyFile.toString()).key;

    const options = getOptions(API_HOSTNAME, DISCOVER_ENDPOINT);
    options.path += `&APPID=${key}`;

    const [rerr, results] = await asyncwrapper(request(options));
    if (rerr) {
        return;
    }
    const main = results.main;
    
    const ifaces = os.networkInterfaces();
    
    let ipaddr = '0.0.0.0';
    Object.keys(ifaces).forEach(iface => {
        // skip loopback
        if (iface !== 'lo' ) { 
            const addr = ifaces[iface].filter(i => {
                return (i.family.toLowerCase() === 'ipv4');
            });
            if (addr && arr.length > 0) {
                ipaddr = addr.map(a => return a.address)[0];
            }
        }
    });

    const updateTime = new Date(),
        formattedDate = formatDate(updateTime),
        formattedTime = formatTime(updateTime);

    const updated = `Last Updated: ${formattedDate} @ ${formattedTime} on ${hostname}/${ipaddr}`;
    const temp = `Current:  ${toFahrenheit(main.temp)}`;
    const tempMin = toFahrenheit(main.temp_min);
    const tempMax = toFahrenheit(main.temp_max);

    const tempRange = `High/Low: ${tempMax}/${tempMin}`;
    const humidity = `Humidity: ${main.humidity}%`;
    const cloudy = `Clouds:   ${results.clouds['all'] || 0}%`;
    const rain = `Rain: ${results.rain && results.rain['1h'] || 0} / ${results.rain && results.rain['3h'] || 0}`;
    
    const data = `${temp}    ${tempRange}${os.EOL}${humidity}    ${cloudy}     ${rain}${os.EOL}${updated}`;

    fs.writeFile('/tmp/details.txt', data, () => {});
    fs.writeFile('/tmp/full.js', `module.exports = ${JSON.stringify(results)};`, () => {});

}

start();
setInterval(() => {
    start();
}, RELOAD);
