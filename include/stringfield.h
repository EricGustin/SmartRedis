/*
 * BSD 2-Clause License
 *
 * Copyright (c) 2021, Hewlett Packard Enterprise
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef SMARTREDIS_STRINGFIELD_H
#define SMARTREDIS_STRINGFIELD_H

#include "metadatafield.h"

namespace SmartRedis {

/*!
*   \brief  The StringField class implements
*   MetadataField class methods needed for
*   storage and transfer of metadata string
*   fields.
*/
class StringField : public MetadataField {

    public:

        /*!
        *   \brief StringField constructor
        *   \param name The name used to reference the string field
        *   \param MetaDataType The metadata type for this field
        */
        StringField(const std::string& name);

        /*!
        *   \brief StringField constructor that
        *          takes in a serialized string to populate values.
        *   \param name The name used to reference the metadata
        *               field
        *   \param serial_string The serialized string containing
        *                        string values
        */
        StringField(const std::string& name,
                    const std::string_view& serial_string);

        /*!
        *   \brief Default StringField copy constructor
        *   \param string_field The string field to be copied.
        */
        StringField(const StringField& string_field) = default;

        /*!
        *   \brief Default StringField move constructor
        *   \param string_field The string field to be moved for construction.
        */
        StringField(StringField&& string_field) = default;

        /*!
        *   \brief Default StringField copy assignment operator
        *   \param string_field The string field to be copied.
        */
        StringField& operator=(const StringField& string_field)
            = default;

        /*!
        *   \brief Default StringField move assignment operator
        *   \param string_field The string field to be moved.
        */
        StringField& operator=(StringField&& string_field)
            = default;

        /*!
        *   \brief Default StringField destructor
        */
        virtual ~StringField() = default;

        /*!
        *   \brief Serialize the StringField for
        *          transmission and storage.  The serialized
        *          buffer returned by the StringField class
        *          contains the number of field values, the
        *          length of each string,
        *          followed by the string values
        *   \returns A string of the serialized field
        */
        virtual std::string serialize();

        /*!
        *   \brief Add a string to the field
        *   \param value A c-ptr to the value to append
        */
        void append(const std::string& value);

        /*!
        *   \brief Retrieve the number of values in the field
        *   \returns The number of values
        */
        virtual size_t size();

        /*!
        *   \brief Clear the values in the field
        */
        virtual void clear();

        /*!
        *   \brief Returns a copy of the underlying field string
        *          values.
        *   \returns std::vector<std::string> of string values
        */
        std::vector<std::string> values();

    private:

        /*!
        *   \brief Unpack the data contained in the buffer.
        *   \param buf The buffer containing ScalarField data.
        */
        void _unpack(const std::string_view& buf);

        /*!
        *   \brief The ScalarField values
        */
        std::vector<std::string> _vals;

        /*!
        *   \brief Put the buffer characters into the
        *          buffer string.
        *   \param buf The buffer in which the characters
        *              should be placed.
        *   \param pos The position in the buffer to place
        *              characters.
        *   \param buf_chars The characters to place in the
        *                    buffer.
        *   \param n_chars The number of characters to place
        *                  in the buffer.
        */
        void _place_buf_chars(std::string& buf,
                              size_t pos,
                              char* buf_chars,
                              size_t n_chars);

};

} //namespace SmartRedis

#endif //SMARTREDIS_STRINGFIELD_H