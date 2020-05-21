import React, { Component } from 'react';

const MONTH_NAMES = [
    'January',
    'February',
    'March',
    'April',
    'May',
    'June',
    'July',
    'August',
    'September',
    'October',
    'November',
    'December',
];

export class Calendar extends Component {
    state = {
        currDate: new Date(),
        daysWithEvents: [],
    };

    getMonthStringFromDate = (date) => {
        return MONTH_NAMES[date.getMonth()];
    };

    generateDays = (date) => {
        const days = [];
        const currDate = new Date(this.state.currDate);
        currDate.setDate(1);
        // Starting from some days from previous month:
        while (currDate.getDay() !== 1) currDate.setDate(currDate.getDate() - 1);

        // Generating the days:
        const daysRows = 6;
        const daysInWeek = 7;

        let dayCounter = 0;
        while (dayCounter < daysRows * daysInWeek) {
            days.push({
                date: currDate.getDate(),
                active: currDate.getMonth() === this.state.currDate.getMonth(),
            });
            currDate.setDate(currDate.getDate() + 1);
            dayCounter++;
        }
        return days;
    };

    onDayClicked = (e) => {
        console.log(e.target.innerText);
    };

    render() {
        const days = this.generateDays(this.state.currDate).map(({ date, active }, i) => (
            <div
                key={i}
                className={`calendar__day ${!active ? 'calendar__day--ghost' : ''}`}
                onClick={this.onDayClicked}
            >
                {date}
            </div>
        ));

        return (
            <div className="calendar">
                <div className="calendar__navbar">
                    <div className="calendar__arrow">L</div>
                    <h1 className="calendar__title">
                        {this.getMonthStringFromDate(this.state.currDate)}
                    </h1>
                    <div className="calendar__arrow">R</div>
                </div>
                <div className="calendar__days-box">{days}</div>
            </div>
        );
    }
}

export default Calendar;
