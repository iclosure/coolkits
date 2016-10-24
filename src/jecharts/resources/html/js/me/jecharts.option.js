"use strict";

var JEchartsOption = function (chart, channel, option) {
    //
    var echartsOption = this;
    this.chart = chart;
    this.channel = channel;
    this.option = option;

    //
    option.titleChanged.connect(function (value) {
        myChart.setOption({title:{text:value}});
    })
}

//required for use with nodejs
if (typeof module === 'object') {
    module.exports = {
        JEchartsOption: JEchartsOption
    };
}