import React, { useState } from 'react';
import TextInput from '../components/TextInput';
import { dateToString } from '../utils';
import Button from '../components/Button';
import TimeInput from '../components/TimeInput';

const Event = (props) => {
    const [descirption, setDescription] = useState(props.descirption);

    const onSubmit = (e) => {
        e.preventDefault();
        console.log('submit');
    };

    return (
        <section className="event-view">
            <h1 className="section-title">New Event on {dateToString(props.currDate)}</h1>
            <form className="event-view__form" onSubmit={onSubmit}>
                <TimeInput label="Time: " />
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
