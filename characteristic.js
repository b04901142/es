var bleno = require('../..');

var BlenoCharacteristic = bleno.Characteristic;

var EchoCharacteristic = function() {
  EchoCharacteristic.super_.call(this, {
    uuid: 'ec0e',
    properties: ['read', 'write', 'notify'],
    value: null
  });

  this._value = new Buffer(0);
  this._updateValueCallback = null;
};

class EchoCharacteristic extends BlenoCharacteristic{
  onReadRequest(offset, callback){
    console.log('EchoCharacteristic - onReadRequest: value = ' + this._value.toString('hex'));
    callback(this.RESULT_SUCCESS, this._value);
  }
  
  onWriteRequest(data, offset, withoutResponse, callback){
    this._value = data;
    console.log('EchoCharacteristic - onWriteRequest: value = ' + this._value.toString('hex'));
    if (this._updateValueCallback) {
      console.log('EchoCharacteristic - onWriteRequest: notifying');
      this._updateValueCallback(this._value);
    }
    callback(this.RESULT_SUCCESS);
  }
  
  onSubscribe(maxValueSize, updateValueCallback){
    console.log('EchoCharacteristic - onSubscribe');
    this._updateValueCallback = updateValueCallback;
  }
  
  
  onUnsubscribe(){
    console.log('EchoCharacteristic - onUnsubscribe');
    this._updateValueCallback = null;
  }
}

module.exports = EchoCharacteristic;
