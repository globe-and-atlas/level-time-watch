var Clay = require('@rebble/clay');

function configuration() {
  return [
    {type: 'heading', defaultValue: 'Level Time'},
    {type: 'text', defaultValue: 'Flat, readable time as your wrist rolls.'},
    {type: 'select', messageKey: 'SETTING_STYLE', label: 'Style', defaultValue: '0', options: [
      {label: 'Ink · white on black', value: '0'},
      {label: 'Paper · charcoal on ivory', value: '1'},
      {label: 'Amber · amber on black', value: '2'},
      {label: 'Field · white on olive', value: '3'},
      {label: 'Signal · white with orange', value: '4'},
      {label: 'Quiet · charcoal on gray', value: '5'}
    ]},
    {type: 'select', messageKey: 'SETTING_DATE', label: 'Date', defaultValue: '0', options: [
      {label: 'Off', value: '0'},
      {label: 'YYYY-MM-DD', value: '1'},
      {label: 'MM/DD/YYYY', value: '2'},
      {label: 'DD/MM/YYYY', value: '3'}
    ]},
    {type: 'submit', defaultValue: 'Save to watch'}
  ];
}

var clay = new Clay(configuration(), null, {autoHandleEvents: false});

function boundedInt(value, minimum, maximum, fallback) {
  var number = Number(value);
  return isFinite(number) && Math.floor(number) === number &&
    number >= minimum && number <= maximum ? number : fallback;
}

function send(raw) {
  var saved;
  try { saved = JSON.parse(raw) || {}; } catch (error) { saved = {}; }
  Pebble.sendAppMessage({
    SETTING_STYLE: boundedInt(saved.SETTING_STYLE, 0, 5, 0),
    SETTING_DATE: boundedInt(saved.SETTING_DATE, 0, 3, 0)
  });
}

Pebble.addEventListener('ready', function () {
  var saved = localStorage.getItem('clay-settings');
  if (saved) send(saved);
});
Pebble.addEventListener('showConfiguration', function () {
  Pebble.openURL(clay.generateUrl());
});
Pebble.addEventListener('webviewclosed', function (event) {
  if (!event || !event.response || event.response === 'CANCELLED') return;
  try { clay.getSettings(event.response); } catch (error) { return; }
  send(localStorage.getItem('clay-settings'));
});

if (typeof module !== 'undefined') module.exports = {configuration: configuration};
