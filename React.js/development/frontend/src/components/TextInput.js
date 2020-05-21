import React, { useState } from 'react';

const TextInput = (props) => {
    const [text, setText] = useState(props.defaultValue || '');

    const onChange = (e) => {
        setText(e.target.value);
        if (props.onChange) props.onChange(e.target.value);
    };

    return (
        <div className="text-input">
            <label className="text-input__label">{props.label}</label>
            <textarea className="text-input__input" type="text" onChange={onChange} value={text} />
        </div>
    );
};

export default TextInput;
