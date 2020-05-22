import React, { useState, useEffect } from 'react';

const TextInput = (props) => {
    // State
    const [text, setText] = useState(props.defaultValue || '');

    // On text input
    const onChange = (e) => {
        setText(e.target.value);
        if (props.onChange) props.onChange(e.target.value);
    };

    // In case event is edited, text might be supplied
    useEffect(() => {
        setText(props.defaultValue);
    }, [props.defaultValue]);

    return (
        <div className="text-input">
            <label className="text-input__label">{props.label}</label>
            <textarea className="text-input__input" type="text" onChange={onChange} value={text} />
        </div>
    );
};

export default TextInput;
