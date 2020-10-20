function addLeadingZero(inNum) {

    const inStr = `${inNum}`;
    if (inStr.length < 2) {
        return `0${inStr}`;
    }
    return inStr;
}

function formatTime(dateObjIn) {
    return `${addLeadingZero(dateObjIn.getHours())}:${addLeadingZero(dateObjIn.getMinutes() + 1)}`;
}

function formatDate(dateObjIn) {
    const year = dateObjIn.getFullYear(),
        month = addLeadingZero(dateObjIn.getMonth() + 1),
        dayOfTheMonth = addLeadingZero(dateObjIn.getDate());
    return `${year}-${month}-${dayOfTheMonth}`;
}

module.exports = {
    addLeadingZero,
    formatTime,
    formatDate
};
