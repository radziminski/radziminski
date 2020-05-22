import React, { useState } from 'react';
import TextInput from '../components/TextInput';
import { dateToString } from '../utils';
import Button from '../components/Button';
import TimeInput from '../components/TimeInput';
import axios from 'axios';

const Event = (props) => {
    const defaultTime = new Date();
    defaultTime.setHours(0, 0, 0, 0);

    const [descirption, setDescription] = useState(props.descirption || '');
    const [time, setTime] = useState(props.time || defaultTime);

    const onSubmit = (e, id = null) => {
        e.preventDefault();
        if (props.isEditing) return updateEvent(id);
        addNewEvent();
    };

    const getFormData = () => {
        //int Year, int Month, int Day, int Hours, int Minutes, string Description
        const data = new FormData();
        const { currDate } = props;
        data.set('Year', currDate.getFullYear());
        data.set('Month', currDate.getMonth() + 1);
        data.set('Day', currDate.getDate());
        data.set('Hours', time.getHours());
        data.set('Minutes', time.getMinutes());
        data.set('Description', descirption);
        return data;
    };

    const updateEvent = (id) => {
        const reqUrl = `http://localhost:3000/api/updateevent`;
        const data = getFormData();
        data.set('Id', id);
        axios
            .post(reqUrl, data, {
                headers: {
                    'Content-Type': 'multipart/form-data',
                },
            })
            .then((data) => {
                props.switchView('day', props.currDate);
            });
    };

    const addNewEvent = () => {
        const reqUrl = `http://localhost:3000/api/addevent`;
        const data = getFormData();
        axios
            .post(reqUrl, data, {
                headers: {
                    'Content-Type': 'multipart/form-data',
                },
            })
            .then((data) => {
                props.switchView('day', props.currDate);
            });
    };

    const title = props.isEditing ? 'Editing Event' : 'New Event';

    return (
        <section className="event-view">
            <h1 className="section-title">
                {title} on {dateToString(props.currDate)}
            </h1>
            <form className="event-view__form" onSubmit={onSubmit}>
                <TimeInput label="Time: " onChange={setTime} default={time} />
                <TextInput onChange={setDescription} label="Description: " />

                <div className="event-view__btns">
                    <Button type="submit" classTypes={['green']}>
                        Add
                    </Button>
                    <Button
                        classTypes={['red']}
                        onClick={() => props.switchView('day', props.currDate)}
                    >
                        Cancel
                    </Button>
                </div>
            </form>
        </section>
    );
};

export default Event;
